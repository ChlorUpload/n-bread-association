#ifndef __H_SESSION__
#define __H_SESSION__

#include "request-handler.h"

#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/config.hpp>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http  = beast::http;          // from <boost/beast/http.hpp>
namespace net   = boost::asio;          // from <boost/asio.hpp>
using tcp       = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>

/// <summary>
/// HTTP 세션을 담당하는 클래스
/// </summary>
class Session
{
  private:
    // Report a failure
    void fail(beast::error_code ec, char const* what)
    {
        std::cerr << what << ": " << ec.message() << "\n";
    }

    // This is the C++11 equivalent of a generic lambda.
    // The function object is used to send an HTTP message.
    template <class Stream>
    struct send_lambda
    {
        Stream&            stream_;
        bool&              close_;
        beast::error_code& ec_;

        explicit send_lambda(Stream&            stream,
                             bool&              close,
                             beast::error_code& ec) :
            stream_(stream),
            close_(close),
            ec_(ec)
        {}

        template <bool isRequest, class Body, class Fields>
        void operator()(http::message<isRequest, Body, Fields>&& msg) const
        {
            // Determine if we should close the connection after
            close_ = msg.need_eof();

            // We need the serializer here because the serializer requires
            // a non-const file_body, and the message oriented version of
            // http::write only works with const messages.
            http::serializer<isRequest, Body, Fields> sr { msg };
            http::write(stream_, sr, ec_);
        }
    };

    // Handles an HTTP server connection
    void do_session(tcp::socket&                              socket,
                    std::shared_ptr<std::string const> const& doc_root)
    {
        bool              close = false;
        beast::error_code ec;

        // This buffer is required to persist across reads
        beast::flat_buffer buffer;

        // This lambda is used to send messages
        send_lambda<tcp::socket> lambda { socket, close, ec };

        for (;;)
        {
            // Read a request
            http::request<http::string_body> req;
            http::read(socket, buffer, req, ec);
            if (ec == http::error::end_of_stream) break;
            if (ec) return fail(ec, "read");

            // Send the response
            _rh.handle_request(*doc_root, std::move(req), lambda);
            if (ec) return fail(ec, "write");
            if (close)
            {
                // This means we should close the connection, usually because
                // the response indicated the "Connection: close" semantic.
                break;
            }
        }

        // Send a TCP shutdown
        socket.shutdown(tcp::socket::shutdown_send, ec);

        // At this point the connection is closed gracefully
    }

    net::io_context                    _ioc;
    boost::asio::ip::address const&    _address;
    const unsigned short               _port;
    std::shared_ptr<std::string> const _doc_root;

    RequestHandler& _rh;

  public:
    Session(RequestHandler&                 rh,
            boost::asio::ip::address const& address,
            const unsigned short            port,
            const char*                     doc_root) :
        _rh { rh },
        _ioc { 1 },
        _address { address },
        _port { port },
        _doc_root { std::make_shared<std::string>(doc_root) }
    {}

    void run()
    {
        // The acceptor receives incoming connections
        tcp::acceptor acceptor { _ioc, { _address, _port } };
        for (;;)
        {
            // This will receive the new connection
            tcp::socket socket { _ioc };

            // Block until we get a connection
            acceptor.accept(socket);

            // Launch the session, transferring ownership of the socket
            std::thread { std::bind(&Session::do_session,
                                    this,
                                    std::move(socket),
                                    _doc_root) }
                .detach();
        }
    }
};

#endif

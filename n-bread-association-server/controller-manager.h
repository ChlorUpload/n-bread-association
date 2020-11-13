#ifndef __H_CONTROLLER_MANAGER__
#define __H_CONTROLLER_MANAGER__

#include "action-manager.h"
#include "controller.h"

#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/config.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http  = beast::http;          // from <boost/beast/http.hpp>
namespace net   = boost::asio;          // from <boost/asio.hpp>
using tcp       = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>

class ControllerManager
{
  private:
    ActionManager&                                               _am;
    std::unordered_map<std::string, std::unique_ptr<Controller>> _controllers;

    std::unordered_map<std::string, std::string>
    _parse_query_str(std::string query_str)
    {
        std::unordered_map<std::string, std::string> map;

        std::stringstream ss { query_str };
        std::string       splited;

        while (std::getline(ss, splited, '&'))
        {
            auto pos = splited.find('=');
            if (pos == std::string::npos) continue;

            map.insert(std::make_pair<std::string, std::string>(
                splited.substr(0, pos),
                splited.substr(pos + 1, std::string::npos)));
        }

        return map;
    }

    std::string _decode(std::string const& input)
    {
        std::string dst;
        // dst.reserve(input.size());
        char   a, b;
        size_t prev_pos = 0, pos = 0;
        while ((pos = input.find('%', pos + 3)) != std::string::npos)
        {
            a = input[pos + 1];
            b = input[pos + 2];

            if (isxdigit(a) && isxdigit(b))
            {
                if (a >= 'a') a -= 'a' - 'A';
                if (a >= 'A') a -= ('A' - 10);
                else
                    a -= '0';
                if (b >= 'a') b -= 'a' - 'A';
                if (b >= 'A') b -= ('A' - 10);
                else
                    b -= '0';

                dst += input.substr(prev_pos, pos - prev_pos);
                dst.push_back(static_cast<const char>(16 * a + b));

                prev_pos = pos + 3;
            }
        }

        dst += input.substr(prev_pos, std::string::npos);

        return dst;
    }

    std::pair<std::string, std::string> _decompose(std::string str)
    {
        auto question_pos = str.find('?');
        if (question_pos == std::string::npos)
        {
            return std::pair<std::string, std::string> {
                str.substr(1, std::string::npos), ""
            };
        }
        else
        {
            return std::pair<std::string, std::string> {
                str.substr(1, question_pos - 1),
                str.substr(question_pos + 1, std::string::npos)
            };
        }
    }

  public:
    ControllerManager(ActionManager& am) : _am { am } {}

    template <typename T>
    ControllerManager& add_controller()
    {
        static_assert(std::is_base_of_v<Controller, T>,
                      "T must be a controller");

        auto controller = std::make_unique<T>(_am);
        auto name       = controller->get_name();

        _controllers.insert(
            std::make_pair(std::move(name), std::move(controller)));

        return *this;
    }

    http::response<http::string_body>
    get_response(http::request<http::string_body>&& req)
    {
        std::unordered_map<std::string, std::string> params;

        std::string request_str { req.target() };
        auto [command, query_str] = _decompose(std::string(request_str));

        if (req.method() == http::verb::get)
        {
            // get method : read query string
            params = _parse_query_str(query_str);
        }
        else if (req.method() == http::verb::post)
        {
            // post method : read body (x-www-form-urlencoded)
            params = _parse_query_str(_decode(req.body()));
        }

        std::cout << "incoming command: " << command << std::endl;

        auto it = _controllers.find(command);
        if (it == _controllers.end())
        {
            http::response<http::string_body> res { http::status::not_found,
                                                    req.version() };
            res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
            res.set(http::field::content_type, "text/html");
            res.keep_alive(req.keep_alive());
            res.body() = "The controller '" + command + "' was not found.";
            res.prepare_payload();
            return res;
        }
        else
        {
            using ControllerResp     = Controller::ControllerResp;
            ControllerResp const& cr = it->second.get()->get_response(params);

            bool status;
            switch (cr.status)
            {
            case ControllerResp::req_status::failed: status = false; break;
            case ControllerResp::req_status::success: status = true; break;
            }

            json response_json
                = { { "status", status },
                    { "log", cr.log },
                    { "failureCode", static_cast<int>(cr.failure) },
                    { "payload", cr.response } };

            http::response<http::string_body> res { http::status::ok,
                                                    req.version() };
            res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
            res.set(http::field::content_type, "application/json");
            res.keep_alive(req.keep_alive());
            res.body() = response_json.dump();
            res.prepare_payload();
            return res;
        }
    }
};

#endif
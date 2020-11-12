#include "action-manager.h"
#include "check-token-query.h"
#include "count-command.h"
#include "credentials-service.h"
#include "db-context.h"
#include "dependency-injection.h"
#include "encryption-service.h"
#include "login-controller.h"
#include "login-query.h"
#include "register-command.h"
#include "session.h"

#define BOOST_DATE_TIME_NO_LIB

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http  = beast::http;          // from <boost/beast/http.hpp>
namespace net   = boost::asio;          // from <boost/asio.hpp>
using tcp       = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>

int main(int argc, char* argv[])
{
    // Check command line arguments.
    if (argc != 4)
    {
        std::cerr << "Usage: http-server-sync <address> <port> <doc_root>\n"
                  << "Example:\n"
                  << "    http-server-sync 0.0.0.0 8080 .\n";
        return EXIT_FAILURE;
    }

    auto const  address  = net::ip::make_address(argv[1]);
    auto const  port     = static_cast<unsigned short>(std::atoi(argv[2]));
    const char* doc_root = argv[3];

    DependencyInjection di;
    ActionManager       am { di };
    ControllerManager   cm { am };
    RequestHandler      rh { cm };
    Session             s { rh, address, port, doc_root };

    cm.add_controller<LoginController>();

    s.run();
}
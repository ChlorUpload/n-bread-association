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
#include "register-controller.h"
#include "session.h"

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/config.hpp>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http  = beast::http;          // from <boost/beast/http.hpp>
namespace net   = boost::asio;          // from <boost/asio.hpp>
using tcp       = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>

int main()
{

    auto const  address  = net::ip::make_address("127.0.0.1");
    auto const  port     = static_cast<unsigned short>(80);
    const char* doc_root = "C:\\doc";

    DependencyInjection di;
    ActionManager       am { di };
    ControllerManager   cm { am };
    RequestHandler      rh { cm };
    Session             s { rh, address, port, doc_root };

    cm.add_controller<LoginController>();
    cm.add_controller<RegisterController>();

    std::cout << "web server started" << std::endl;
    s.run();
}
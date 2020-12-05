#include "action-manager.h"
#include "check-token-controller.h"
#include "check-token-query.h"
#include "credentials-service.h"
#include "db-context.h"
#include "dependency-injection.h"
#include "encryption-service.h"
#include "login-controller.h"
#include "login-query.h"
#include "register-command.h"
#include "register-controller.h"
#include "session.h"

#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/config.hpp>
#include <cstdlib>
#include <get-products-controller.h>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http  = beast::http;          // from <boost/beast/http.hpp>
namespace net   = boost::asio;          // from <boost/asio.hpp>
using tcp       = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>

int main()
{
    /* 서버 실행을 위한 정보 */
    // 서버 IP
    auto const address = net::ip::make_address("127.0.0.1");
    // 서버 포트
    auto const port = static_cast<unsigned short>(80);
    // 서버에 파일 조회 요청이 들어왔을 때 읽을 루트 디렉토리
    const char* doc_root = "C:\\doc";

    DependencyInjection di;
    ActionManager       am { di };
    ControllerManager   cm { am };
    Session             s { cm, address, port, doc_root };

    // 컨트롤러 매니저에 컨트롤러 추가
    cm.add_controller<LoginController>()
        .add_controller<RegisterController>()
        .add_controller<CheckTokenController>()
        .add_controller<GetProductsController>();

    // 웹 서버 실행
    std::cout << "web server started" << std::endl;
    s.run();
}
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
    /* ���� ������ ���� ���� */
    // ���� IP
    auto const address = net::ip::make_address("127.0.0.1");
    // ���� ��Ʈ
    auto const port = static_cast<unsigned short>(80);
    // ������ ���� ��ȸ ��û�� ������ �� ���� ��Ʈ ���丮
    const char* doc_root = "C:\\doc";

    DependencyInjection di;
    ActionManager       am { di };
    ControllerManager   cm { am };
    Session             s { cm, address, port, doc_root };

    // ��Ʈ�ѷ� �Ŵ����� ��Ʈ�ѷ� �߰�
    cm.add_controller<LoginController>()
        .add_controller<RegisterController>()
        .add_controller<CheckTokenController>()
        .add_controller<GetProductsController>();

    // �� ���� ����
    std::cout << "web server started" << std::endl;
    s.run();
}
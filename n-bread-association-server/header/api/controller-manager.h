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

/// <summary>
/// ��Ʈ�ѷ��� �����ϴ� Ŭ����
/// </summary>
class ControllerManager
{
  private:
    /// <summary>
    /// �׼� �Ŵ����� �� ��Ʈ�ѷ����� �Ѱ��ݴϴ�.
    /// </summary>
    ActionManager&                                               _am;
    std::unordered_map<std::string, std::unique_ptr<Controller>> _controllers;

    /// <summary>
    /// ���� ��Ʈ���� �Ľ��� map�� �޾ƿɴϴ�.
    /// </summary>
    /// <param name="query_str">���� ��Ʈ��</param>
    /// <returns>���� ��Ʈ���� �º��� key��, �캯�� value�� ���� map</returns>
    std::unordered_map<std::string, std::string>
    _parse_query_str(std::string const& query_str);

    /// <summary>
    /// �ۼ�Ʈ ���ڵ��� �� ���ڿ��� ���ڵ��� �޾ƿɴϴ�.
    /// </summary>
    /// <param name="str">�ۼ�Ʈ ���ڵ� �� ���ڿ�</param>
    /// <returns>���ڵ� �� ���ڿ�</returns>
    std::string _decode(std::string const& str);

    /// <summary>
    /// ���� ��Ʈ���� ����ǥ ��ȣ �ڷ� �پ��ִ� ������ ���ڿ��� ����ǥ
    /// ������ command name�� �� ������ ���� ��Ʈ������ �и��� �޾ƿɴϴ�.
    /// </summary>
    /// <param name="str"></param>
    /// <returns></returns>
    std::pair<std::string, std::string> _decompose(std::string const& str);

  public:
    ControllerManager(ActionManager& am) : _am { am } {}

    /// <summary>
    /// ��Ʈ�ѷ� �Ŵ������� HTTP ������Ʈ�� ó���� �� �ִ� ��Ʈ�ѷ��� ������Ʈ
    /// ������ �ѱ⵵�� ��Ű�� �� ��Ʈ�ѷ��κ��� �޾ƿ� ������ ������ json��
    /// client���� ������ ���������� �޾ƿɴϴ�.
    /// </summary>
    /// <param name="req">HTTP ������Ʈ</param>
    /// <returns>HTTP ��������</returns>
    http::response<http::string_body>
    get_response(http::request<http::string_body>&& req);

    /// <summary>
    /// ��Ʈ�ѷ��� �߰��մϴ�. ���������� �� �Լ��� ȣ���� �� �ֽ��ϴ�.
    /// </summary>
    /// <typeparam name="T">��Ʈ�ѷ�</typeparam>
    /// <returns>��Ʈ�ѷ� �Ŵ���</returns>
    template <typename T>
    ControllerManager& add_controller()
    {
        static_assert(std::is_base_of_v<Controller, T>,
                      "T must be a controller");

        auto controller = std::make_unique<T>(_am);
        auto name       = controller->get_name();

        // ��Ʈ�ѷ��� ��Ʈ�ѷ� �迭�� ����ֽ��ϴ�.
        _controllers.insert(
            std::make_pair(std::move(name), std::move(controller)));

        return *this;
    }
};

#endif
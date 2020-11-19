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
/// 컨트롤러를 관리하는 클래스
/// </summary>
class ControllerManager
{
  private:
    /// <summary>
    /// 액션 매니저를 각 컨트롤러에게 넘겨줍니다.
    /// </summary>
    ActionManager&                                               _am;
    std::unordered_map<std::string, std::unique_ptr<Controller>> _controllers;

    /// <summary>
    /// 쿼리 스트링을 파싱한 map을 받아옵니다.
    /// </summary>
    /// <param name="query_str">쿼리 스트링</param>
    /// <returns>쿼리 스트링의 좌변을 key로, 우변을 value로 갖는 map</returns>
    std::unordered_map<std::string, std::string>
    _parse_query_str(std::string const& query_str);

    /// <summary>
    /// 퍼센트 인코딩이 된 문자열을 디코딩해 받아옵니다.
    /// </summary>
    /// <param name="str">퍼센트 인코딩 된 문자열</param>
    /// <returns>디코딩 된 문자열</returns>
    std::string _decode(std::string const& str);

    /// <summary>
    /// 쿼리 스트링이 물음표 기호 뒤로 붙어있는 형태의 문자열을 물음표
    /// 이전의 command name과 그 이후의 쿼리 스트링으로 분리해 받아옵니다.
    /// </summary>
    /// <param name="str"></param>
    /// <returns></returns>
    std::pair<std::string, std::string> _decompose(std::string const& str);

  public:
    ControllerManager(ActionManager& am) : _am { am } {}

    /// <summary>
    /// 컨트롤러 매니저에게 HTTP 리퀘스트를 처리할 수 있는 컨트롤러로 리퀘스트
    /// 정보를 넘기도록 시키고 그 컨트롤러로부터 받아온 정보가 가공된 json을
    /// client에게 보내는 리스폰스를 받아옵니다.
    /// </summary>
    /// <param name="req">HTTP 리퀘스트</param>
    /// <returns>HTTP 리스폰스</returns>
    http::response<http::string_body>
    get_response(http::request<http::string_body>&& req);

    /// <summary>
    /// 컨트롤러를 추가합니다. 연쇄적으로 이 함수를 호출할 수 있습니다.
    /// </summary>
    /// <typeparam name="T">컨트롤러</typeparam>
    /// <returns>컨트롤러 매니저</returns>
    template <typename T>
    ControllerManager& add_controller()
    {
        static_assert(std::is_base_of_v<Controller, T>,
                      "T must be a controller");

        auto controller = std::make_unique<T>(_am);
        auto name       = controller->get_name();

        // 컨트롤러를 컨트롤러 배열에 집어넣습니다.
        _controllers.insert(
            std::make_pair(std::move(name), std::move(controller)));

        return *this;
    }
};

#endif
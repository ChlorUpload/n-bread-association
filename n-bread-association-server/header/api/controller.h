#ifndef __H_CONTROLLER__
#define __H_CONTROLLER__

#include "action-manager.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

/// <summary>
/// 컨트롤러의 베이스 클래스. 모든 컨트롤러는 이 클래스를 상속합니다.
/// </summary>
class Controller
{
  protected:
    /// <summary>
    /// 컨트롤러는 액션 매니저에게 액션 실행을 요청합니다.
    /// </summary>
    ActionManager& _am;

  public:
    /// <summary>
    /// 컨트롤러가 반환하는 타입. 리스폰스 상태, 실패 코드, 로그, 정보를 담은
    /// JSON 객체를 담는 클래스.
    /// </summary>
    struct ControllerResp
    {
        /// <summary>
        /// 요청 상태
        /// </summary>
        enum class res_status
        {
            /// <summary>
            /// 요청 성공
            /// </summary>
            success = 0,
            /// <summary>
            /// 요청 실패
            /// </summary>
            failed = 1,
        };

        /// <summary>
        /// 실패 코드
        /// </summary>
        enum class failure_code
        {
            /// <summary>
            /// 정상 (기본값)
            /// </summary>
            ok = 0,
            /// <summary>
            /// 비정상적인 인수
            /// </summary>
            invalid_argument,
            /// <summary>
            /// 액세스 거부
            /// </summary>
            access_denied,
            /// <summary>
            /// 중복 이메일
            /// </summary>
            duplicate_email,
            /// <summary>
            /// 잘못된 액세스 토큰
            /// </summary>
            invalid_token,
            /// <summary>
            /// 알 수 없는 오류
            /// </summary>
            unknown_error,
        };

        res_status   status;
        failure_code failure;
        std::string  log;
        json         response;
    };

    Controller(ActionManager& am) : _am { am } {}

    /// <summary>
    /// 컨트롤러에게 params 객체를 주고 ControllerResp 객체를 받아옵니다.
    /// </summary>
    /// <param name="params">쿼리 스트링의 좌변을 key로, 우변을 value로 갖는 map</param>
    /// <returns></returns>
    virtual ControllerResp
    get_response(std::unordered_map<std::string, std::string> const& params)
        = 0;

    /// <summary>
    /// 컨트롤러의 이름을 받아옵니다.
    /// </summary>
    /// <returns>컨트롤러 이름</returns>
    virtual std::string get_name() = 0;
};

#endif
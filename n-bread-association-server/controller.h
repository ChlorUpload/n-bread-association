#ifndef __H_CONTROLLER__
#define __H_CONTROLLER__

#include "action-manager.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Controller
{
  protected:
    ActionManager& _am;

  public:
    struct ControllerResp
    {
        enum class req_status
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

        enum class failure_code
        {
            /// <summary>
            /// 정상 (기본값)
            /// </summary>
            ok,
            /// <summary>
            /// 비정상적인 인수
            /// </summary>
            invalid_argument,
            /// <summary>
            /// 액세스 거부
            /// </summary>
            access_denied,
            /// <summary>
            /// 알 수 없는 오류
            /// </summary>
            unknown_error,
        };

        req_status   status;
        failure_code failure;
        std::string  log;
        json         response;
    };

    Controller(ActionManager& am) : _am { am } {}

    virtual ControllerResp
    get_response(std::unordered_map<std::string, std::string> params)
        = 0;

    virtual std::string get_name() = 0;
};

#endif
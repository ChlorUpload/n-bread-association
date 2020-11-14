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
            /// ��û ����
            /// </summary>
            success = 0,
            /// <summary>
            /// ��û ����
            /// </summary>
            failed = 1,
        };

        enum class failure_code
        {
            /// <summary>
            /// ���� (�⺻��)
            /// </summary>
            ok = 0,
            /// <summary>
            /// ���������� �μ�
            /// </summary>
            invalid_argument,
            /// <summary>
            /// �׼��� �ź�
            /// </summary>
            access_denied,
            /// <summary>
            /// �ߺ� �̸���
            /// </summary>
            duplicate_email,
            /// <summary>
            /// �� �� ���� ����
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
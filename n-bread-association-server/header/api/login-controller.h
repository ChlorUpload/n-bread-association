#ifndef __H_LOGIN_CONTROLLER__
#define __H_LOGIN_CONTROLLER__

#include "action-manager.h"
#include "controller.h"
#include "login-query.h"

/// <summary>
/// �α��� ������Ʈ�� ó���ϴ� ��Ʈ�ѷ�
/// </summary>
class LoginController : public Controller
{
  public:
    using Controller::Controller;

    virtual ControllerResp
    get_response(std::unordered_map<std::string, std::string> const& params) override
    {
        auto email_it    = params.find("email");
        auto password_it = params.find("password");

        if (email_it == params.end() || password_it == params.end())
        {
            // �̸��ϰ� ��й�ȣ�� ������ �ʾ��� ��, invalid_argument�� ��ȯ�մϴ�.
            json           json_token = { { "token", "" } };
            ControllerResp cr { ControllerResp::req_status::failed,
                                ControllerResp::failure_code::invalid_argument,
                                "one or more arguments are missing",
                                json_token };
            return cr;
        }
        else
        {
            auto email    = email_it->second;
            auto password = password_it->second;

            // LoginQuery �׼��� �����մϴ�.
            auto [state, token] = _am(LoginQuery { email, password });

            if (state == LoginState::success)
            {
                // ���� �� �׼��� ��ū�� ��ȯ�մϴ�.
                json           json_token = { { "token", token } };
                ControllerResp cr { ControllerResp::req_status::success,
                                    ControllerResp::failure_code::ok,
                                    "",
                                    json_token };
                return cr;
            }
            else
            {
                // ���� �� access_denied�� ��ȯ�մϴ�.
                json           json_token = { { "token", "" } };
                ControllerResp cr { ControllerResp::req_status::failed,
                                    ControllerResp::failure_code::access_denied,
                                    "email or password is not correct",
                                    json_token };
                return cr;
            }
        }
    }

    virtual std::string get_name() override
    {
        return "login";
    }
};

#endif
#ifndef __H_REGISTER_CONTROLLER__
#define __H_REGISTER_CONTROLLER__

#include "action-manager.h"
#include "controller.h"
#include "register-command.h"

/// <summary>
/// 회원가입 리퀘스트를 처리하는 컨트롤러
/// </summary>
class RegisterController : public Controller
{
  public:
    using Controller::Controller;

    virtual ControllerResp get_response(
        std::unordered_map<std::string, std::string> const& params) override
    {
        auto name_it     = params.find("name");
        auto email_it    = params.find("email");
        auto password_it = params.find("password");
        auto phone_it    = params.find("phone");

        if (name_it == params.end() || email_it == params.end()
            || password_it == params.end() || phone_it == params.end())
        {
            // 정보가 모두 들어오지 않았을 경우, invalid_argument를 반환합니다.
            json           res = {};
            ControllerResp cr { ControllerResp::req_status::failed,
                                ControllerResp::failure_code::invalid_argument,
                                "one or more arguments are missing",
                                res };
            return cr;
        }
        else
        {
            auto name     = name_it->second;
            auto email    = email_it->second;
            auto password = password_it->second;
            auto phone    = phone_it->second;

            // RegisterCommand 액션을 실행합니다.
            bool res = _am(RegisterCommand { name, email, password, phone });

            if (res)
            {
                // 성공 시
                json           res = {};
                ControllerResp cr { ControllerResp::req_status::success,
                                    ControllerResp::failure_code::ok,
                                    "successfully registered",
                                    res };
                return cr;
            }
            else
            {
                // 실패 시, duplicate_email을 반환합니다.
                json           res = {};
                ControllerResp cr {
                    ControllerResp::req_status::failed,
                    ControllerResp::failure_code::duplicate_email,
                    "there is a duplicate email",
                    res
                };
                return cr;
            }
        }
    }

    virtual std::string get_name() override
    {
        return "register";
    }
};

#endif
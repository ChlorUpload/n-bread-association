#ifndef __H_LOGIN_CONTROLLER__
#define __H_LOGIN_CONTROLLER__

#include "action-manager.h"
#include "controller.h"
#include "login-query.h"

class LoginController : public Controller
{
  public:
    using Controller::Controller;

    virtual ControllerResp
    get_response(std::unordered_map<std::string, std::string> params) override
    {
        for (auto& v : params)
        { std::cout << v.first << ", " << v.second << std::endl; }

        auto email_it    = params.find("email");
        auto password_it = params.find("password");

        if (email_it == params.end() || password_it == params.end())
        {
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

            auto [state, token] = _am(LoginQuery { email, password });

            if (state == LoginState::success)
            {
                json           json_token = { { "token", token } };
                ControllerResp cr { ControllerResp::req_status::success,
                                    ControllerResp::failure_code::ok,
                                    "",
                                    json_token };
                return cr;
            }
            else
            {
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
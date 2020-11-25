#ifndef __H_CHECK_TOKEN_CONTROLLER__
#define __H_CHECK_TOKEN_CONTROLLER__

#include "action-manager.h"
#include "check-token-query.h"
#include "controller.h"

class CheckTokenController : public Controller
{
  public:
    using Controller::Controller;

    virtual ControllerResp get_response(
        std::unordered_map<std::string, std::string> const& params) override
    {
        auto token_it = params.find("accessToken");

        for (auto& v : params)
        { std::cout << v.first << ", " << v.second << std::endl; }

        if (token_it == params.end())
        {
            json           res = {};
            ControllerResp cr { ControllerResp::res_status::failed,
                                ControllerResp::failure_code::invalid_argument,
                                "access token is missing",
                                res };
            return cr;
        }
        else
        {
            auto token = token_it->second;
            bool res   = _am(CheckTokenQuery(token));

            if (res)
            {
                json           res = {};
                ControllerResp cr { ControllerResp::res_status::success,
                                    ControllerResp::failure_code::ok,
                                    "valid access token",
                                    res };
                return cr;
            }
            else
            {
                json           res = {};
                ControllerResp cr { ControllerResp::res_status::failed,
                                    ControllerResp::failure_code::invalid_token,
                                    "invalid access token",
                                    res };
                return cr;
            }
        }
    }

    virtual std::string get_name() override
    {
        return "checkToken";
    }
};

#endif
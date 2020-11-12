#ifndef __H_LOGIN_CONTROLLER__
#define __H_LOGIN_CONTROLLER__

#include "action-manager.h"
#include "controller.h"

class LoginController : public Controller
{
  public:
    using Controller::Controller;

    virtual std::string
    get_response(std::unordered_map<std::string, std::string> params) override
    {
        return R"==({"daegeon": "hehe"})==";
    }

    virtual std::string get_name() override
    {
        return "login";
    }
};

#endif
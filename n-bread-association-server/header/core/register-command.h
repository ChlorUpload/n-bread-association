#ifndef __H_REGISTER_COMMAND__
#define __H_REGISTER_COMMAND__

#include "action.h"

#include <string>

/// <summary>
/// 회원 가입 커맨드
/// </summary>
struct RegisterCommand : Action<bool>
{
    std::string name, email, password, phone;

    RegisterCommand(std::string const& name,
                    std::string const& email,
                    std::string const& password,
                    std::string const& phone) :
        name { name },
        email { email },
        password { password },
        phone { phone }
    {}
};

#endif
#include "action-manager.h"
#include "check-token-query.h"
#include "count-command.h"
#include "credentials-service.h"
#include "db-context.h"
#include "dependency-injection.h"
#include "encryption-service.h"
#include "login-query.h"
#include "register-command.h"

#include <iostream>
#include <string>

int main(void)
{
    DependencyInjection di;
    ActionManager       am { di };

    std::string email, password;

     //std::cout << "이메일을 입력해주세요 :";
     //std::cin >> email;
     //std::cout << "비밀번호를 입력해주세요 :";
     //std::cin >> password;

    email    = "ghahddl@dgist.ac.kr";
    password = "password123";

    auto [state, res] = am(LoginQuery { email, password });
    std::string token = "";

    switch (state)
    {
    case LoginState::success:
        std::cout << "logged in! access token: " << (token = res) << std::endl;
        break;
    case LoginState::no_email: std::cout << "invalid email" << std::endl; break;
    case LoginState::pw_mismatch:
        std::cout << "invalid password" << std::endl;
        break;
    default: break;
    }

    std::cout << "check if token is valid: " << std::boolalpha
              << am(CheckTokenQuery { token }) << std::endl;

    // Register
    am(RegisterCommand {
        u8"김찬중", "paxbun@dgist.ac.kr", "password", "01027725813" });
}
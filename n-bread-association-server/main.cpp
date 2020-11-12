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

     //std::cout << "�̸����� �Է����ּ��� :";
     //std::cin >> email;
     //std::cout << "��й�ȣ�� �Է����ּ��� :";
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
        u8"������", "paxbun@dgist.ac.kr", "password", "01027725813" });
}
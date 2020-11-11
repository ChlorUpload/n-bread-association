#include "action-manager.h"
#include "check-token-query.h"
#include "count-command.h"
#include "credentials-manager.h"
#include "dependency-injection.h"

#include <iostream>
#include <string>

int main(void)
{
    DependencyInjection di;
    ActionManager       am { di };

    am(CountCommand { 10 });
    am(CheckTokenQuery { std::string("access token") });

    auto cm = di.GetService<CredentialsManager>();
    std::string token = cm.create_token("songdaegeon");
    std::cout << token << std::endl;
    std::cout << std::boolalpha << cm.verify_token(token) << std::endl;
    std::cout << cm.get_user_id(token) << std::endl;
}
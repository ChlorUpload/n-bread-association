#include <iostream>
#include <string>

#include "action-manager.h"
#include "count-command.h"
#include "check-token-query.h"
#include "dependency-injection.h"

int main(void)
{
    DependencyInjection di;
    ActionManager am{di};

    am(CountCommand{10});
    am(CheckTokenQuery{std::string("access token")});
}
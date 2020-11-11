#include "action-manager.h"
#include "check-token-query.h"
#include "count-command.h"
#include "dependency-injection.h"

#include <iostream>
#include <string>

int main(void)
{
    DependencyInjection di;
    ActionManager       am { di };

    am(CountCommand { 10 });
    am(CheckTokenQuery { std::string("access token") });
}
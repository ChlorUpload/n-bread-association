#include <iostream>

#include "action-manager.h"
#include "count-command.h"
#include "db-context.h"

int main(void)
{
    DbContext ctx;
    ActionManager am{&ctx};

    am(CountCommand{10});
}
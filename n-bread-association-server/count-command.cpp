#include "count-command.h"

#include <iostream>

template <>
void ActionHandler<CountCommand>::operator()(CountCommand const& action)
{
    std::cout << action.param << std::endl;
}

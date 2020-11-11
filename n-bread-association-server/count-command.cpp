#include <iostream>
#include <memory>

#include "count-command.h"
#include "db-context.h"

template <>
struct ActionHandler<CountCommand>::Impl
{
    DbContext& ctx;

    Impl(DbContext& ctx)
        : ctx{ctx}
    { }
};

template <>
ActionHandler<CountCommand>::ActionHandler(DependencyInjection& di)
    : pImpl{std::make_unique<Impl>(di.GetService<DbContext>())}
{ }

template <>
ActionHandler<CountCommand>::~ActionHandler()
{ }

template <>
void ActionHandler<CountCommand>::operator()(CountCommand const& action)
{
    std::cout << action.param << std::endl;
}

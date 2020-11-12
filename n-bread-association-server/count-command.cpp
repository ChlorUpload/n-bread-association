#include "count-command.h"

#include "db-context.h"

#include <iostream>
#include <memory>

template <>
struct ActionHandler<CountCommand>::Impl
{
    DbContext& ctx;

    Impl(DbContext& ctx) : ctx { ctx } {}
};

template <>
ActionHandler<CountCommand>::ActionHandler(DependencyInjection& di) :
    pImpl { std::make_unique<Impl>(di.get_service<DbContext>()) }
{}

template <>
ActionHandler<CountCommand>::~ActionHandler()
{}

template <>
void ActionHandler<CountCommand>::operator()(CountCommand const& action)
{
    std::cout << action.param << std::endl;
}

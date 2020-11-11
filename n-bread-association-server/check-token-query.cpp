#include "check-token-query.h"

#include "credentials-manager.h"
#include "db-context.h"

#include <memory>

template <>
struct ActionHandler<CheckTokenQuery>::Impl
{
    CredentialsManager& cm;
    DbContext&          ctx;

    Impl(CredentialsManager& cm, DbContext& ctx) : cm { cm }, ctx { ctx } {}
};

template <>
ActionHandler<CheckTokenQuery>::ActionHandler(DependencyInjection& di) :
    pImpl { std::make_unique<Impl>(di.GetService<CredentialsManager>(),
                                   di.GetService<DbContext>()) }
{}

template <>
ActionHandler<CheckTokenQuery>::~ActionHandler()
{}

template <>
bool ActionHandler<CheckTokenQuery>::operator()(CheckTokenQuery const& action)
{
    std::cout << action.access_token << std::endl;
    return true;
}

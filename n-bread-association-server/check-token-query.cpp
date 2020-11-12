#include "check-token-query.h"

#include "credentials-service.h"
#include "db-context.h"

#include <memory>

template <>
struct ActionHandler<CheckTokenQuery>::Impl
{
    CredentialsService& cm;
    DbContext&          ctx;

    Impl(CredentialsService& cm, DbContext& ctx) : cm { cm }, ctx { ctx } {}
};

template <>
ActionHandler<CheckTokenQuery>::ActionHandler(DependencyInjection& di) :
    pImpl { std::make_unique<Impl>(di.GetService<CredentialsService>(),
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

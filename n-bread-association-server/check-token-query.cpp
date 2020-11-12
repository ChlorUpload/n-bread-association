#include "check-token-query.h"

#include "credentials-service.h"
#include "db-context.h"

#include <memory>

template <>
struct ActionHandler<CheckTokenQuery>::Impl
{
    CredentialsService& cs;

    Impl(CredentialsService& cs) : cs { cs } {}
};

template <>
ActionHandler<CheckTokenQuery>::ActionHandler(DependencyInjection& di) :
    pImpl { std::make_unique<Impl>(di.get_service<CredentialsService>()) }
{}

template <>
ActionHandler<CheckTokenQuery>::~ActionHandler()
{}

template <>
bool ActionHandler<CheckTokenQuery>::operator()(CheckTokenQuery const& action)
{
    return pImpl->cs.verify_token(action.access_token);
}

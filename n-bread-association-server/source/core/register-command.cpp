#include "register-command.h"

#include "db-context.h"
#include "encryption-service.h"

#include <iostream>
#include <memory>

template <>
struct ActionHandler<RegisterCommand>::Impl
{
    DbContext&         ctx;
    EncryptionService& es;

    Impl(DbContext& ctx, EncryptionService& es) : ctx { ctx }, es { es } {}
};

template <>
ActionHandler<RegisterCommand>::ActionHandler(DependencyInjection& di) :
    pImpl { std::make_unique<Impl>(di.get_service<DbContext>(),
                                   di.get_service<EncryptionService>()) }
{}

template <>
ActionHandler<RegisterCommand>::~ActionHandler()
{}

template <>
bool ActionHandler<RegisterCommand>::operator()(RegisterCommand const& action)
{
    if (pImpl->ctx.get_user_id(action.email) != -1) { return false; }

    std::string encrypted_pw = pImpl->es.encrypt(action.password);
    pImpl->ctx.add_user(action.name, action.email, encrypted_pw, action.phone);
    return true;
}

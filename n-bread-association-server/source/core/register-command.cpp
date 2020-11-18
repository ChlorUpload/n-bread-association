#include "register-command.h"

#include "db-context.h"
#include "encryption-service.h"

#include <algorithm>
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
    std::vector<User> const& v = pImpl->ctx.read<User>();
    auto user_it = std::find_if(v.begin(), v.end(), [&](User const& u) {
        return u.email == action.email;
    });

    if (user_it != v.end()) { return false; }

    User user;
    user.email        = action.email;
    user.encrypted_pw = pImpl->es.encrypt(action.password);
    user.name         = action.name;
    user.phone        = action.phone;
    user.verified     = false;

    pImpl->ctx.create<User>(user);
    return true;
}

#include "login-query.h"

#include "credentials-service.h"
#include "db-context.h"
#include "encryption-service.h"

template <>
struct ActionHandler<LoginQuery>::Impl
{
    CredentialsService& cs;
    DbContext&          ctx;
    EncryptionService&  es;

    Impl(CredentialsService& cs, DbContext& ctx, EncryptionService& es) :
        cs { cs },
        ctx { ctx },
        es { es }
    {}
};

template <>
ActionHandler<LoginQuery>::ActionHandler(DependencyInjection& di) :
    pImpl { std::make_unique<Impl>(di.get_service<CredentialsService>(),
                                   di.get_service<DbContext>(),
                                   di.get_service<EncryptionService>()) }
{}

template <>
ActionHandler<LoginQuery>::~ActionHandler()
{}

template <>
std::pair<LoginState, std::string>
ActionHandler<LoginQuery>::operator()(LoginQuery const& action)
{
    int user_id = pImpl->ctx.get_user_id(action.email);
    if (user_id == -1)
    {
        return std::make_pair<LoginState, std::string>(LoginState::no_email,
                                                       "");
    }

    std::string encrypted_db_pw = pImpl->ctx.get_user_encrypted_pw(user_id);
    std::string encrypted_pw    = pImpl->es.encrypt(action.password);

    if (encrypted_db_pw == encrypted_pw)
    {
        return std::make_pair<LoginState, std::string>(
            LoginState::success, pImpl->cs.create_token(user_id));
    }
    
    return std::make_pair<LoginState, std::string>(LoginState::pw_mismatch, "");
}

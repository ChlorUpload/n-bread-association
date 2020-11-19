#include "login-query.h"

#include "credentials-service.h"
#include "db-context.h"
#include "encryption-service.h"
#include "user.h"

#include <algorithm>

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
    // 유저 정보를 가져옵니다.
    std::vector<User> const& v = pImpl->ctx.read<User>();

    // 유저 정보에서 이메일이 일치하는 유저를 찾습니다.
    auto user_it = std::find_if(
        v.begin(), v.end(), [&](User const& u) { return u.email == action.email; });

    if (user_it == v.end())
    {
        // 존재하지 않는다면 no_email LoginState를 반환합니다.
        return std::make_pair<LoginState, std::string>(LoginState::no_email,
                                                       "");
    }

    // 컨트롤러로부터 받아온 비밀번호를 암호화하여 모델의 비밀번호와 비교합니다.
    std::string encrypted_db_pw = user_it->encrypted_pw;
    std::string encrypted_pw    = pImpl->es.encrypt(action.password);

    if (encrypted_db_pw == encrypted_pw)
    {
        // 비밀번호가 서로 일치한다면, 유저 아이디로 액세스 토큰을 발급합니다.
        return std::make_pair<LoginState, std::string>(
            LoginState::success, pImpl->cs.create_token(user_it->id));
    }

    // 비밀번호가 일치하지 않을 시, pw_mismatch LoginState를 반환합니다.
    return std::make_pair<LoginState, std::string>(LoginState::pw_mismatch, "");
}

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
    // ���� ������ �����ɴϴ�.
    std::vector<User> const& v = pImpl->ctx.read<User>();

    // ���� �������� �̸����� ��ġ�ϴ� ������ ã���ϴ�.
    auto user_it = std::find_if(
        v.begin(), v.end(), [&](User const& u) { return u.email == action.email; });

    if (user_it == v.end())
    {
        // �������� �ʴ´ٸ� no_email LoginState�� ��ȯ�մϴ�.
        return std::make_pair<LoginState, std::string>(LoginState::no_email,
                                                       "");
    }

    // ��Ʈ�ѷ��κ��� �޾ƿ� ��й�ȣ�� ��ȣȭ�Ͽ� ���� ��й�ȣ�� ���մϴ�.
    std::string encrypted_db_pw = user_it->encrypted_pw;
    std::string encrypted_pw    = pImpl->es.encrypt(action.password);

    if (encrypted_db_pw == encrypted_pw)
    {
        // ��й�ȣ�� ���� ��ġ�Ѵٸ�, ���� ���̵�� �׼��� ��ū�� �߱��մϴ�.
        return std::make_pair<LoginState, std::string>(
            LoginState::success, pImpl->cs.create_token(user_it->id));
    }

    // ��й�ȣ�� ��ġ���� ���� ��, pw_mismatch LoginState�� ��ȯ�մϴ�.
    return std::make_pair<LoginState, std::string>(LoginState::pw_mismatch, "");
}

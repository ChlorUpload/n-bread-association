#include "db-context.h"
#include "dependency-injection.h"
#include "user.h"

int main(void)
{
    DependencyInjection di;
    DbContext&          ctx = di.get_service<DbContext>();

    User u;
    u.email        = "test-email@dgist.ac.kr";
    u.encrypted_pw = "test-password";
    u.name         = "test-name";
    u.phone        = "01012341234";
    u.verified     = false;
    ctx.create<User>(u);

    auto& v = ctx.read<User>();

    auto it = std::find_if(v.begin(), v.end(), [&](User const& a) {
        return a.email == u.email && a.encrypted_pw == u.encrypted_pw
               && a.name == u.name && a.phone == u.phone
               && a.verified == a.verified;
    });

    if (it == v.end()) return 1;

    return 0;
}
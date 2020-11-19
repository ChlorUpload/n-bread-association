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

    auto& v = ctx.read<User>();

    std::cout << v.size() << std::endl;

    for (auto& elem : v) std::cout << elem.email << elem.encrypted_pw << elem.name << elem.phone << elem.verified << std::endl;

    auto it = std::find_if(v.begin(), v.end(), [&](User const& a) {
        return a.email == u.email && a.encrypted_pw == u.encrypted_pw
               && a.name == u.name && a.phone == u.phone
               && a.verified == u.verified;
    });

    if (it == v.end()) return 1;

    std::cout << "read 성공, 아이디 : " << it->id << std::endl;

    try
    {
        if (!ctx.remove<User>(it->id)) { return 2; }
    }
    catch (...)
    {
        return 3;
    }

    std::cout << "remove 성공" << std::endl;

    auto& v2 = ctx.read<User>();
    auto  it2 = std::find_if(v.begin(), v.end(), [&](User const& a) {
        return a.email == u.email && a.encrypted_pw == u.encrypted_pw
               && a.name == u.name && a.phone == u.phone
               && a.verified == a.verified;
    });

    if (it2 != v2.end()) return 4;

    std::cout << "remove 확인" << std::endl;

    return 0;
}
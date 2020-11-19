#include "db-context.h"
#include "dependency-injection.h"
#include "user.h"

#include <ctime>
#include <iostream>

int main(void)
{
    DependencyInjection di;
    DbContext&          ctx = di.get_service<DbContext>();

    try
    {
        /* add test */

        /* add category test */
        std::cout << "add category test" << std::endl;

        Category c;
        c.name = "test-name";
        ctx.create<Category>(c);

        auto& vc = ctx.read<Category>();

        auto& c_it = std::find_if(vc.begin(), vc.end(), [&](Category const& a) {
            return a.id == c.id;
        });

        if (c_it == vc.end()) return 1;

        /* user add test */
        std::cout << "add user test" << std::endl;

        User u;
        u.email        = "test-email@dgist.ac.kr";
        u.encrypted_pw = "test-password";
        u.name         = "test-name";
        u.phone        = "01012341234";
        u.verified     = false;
        ctx.create<User>(u);

        auto& vu = ctx.read<User>();

        auto& u_it = std::find_if(
            vu.begin(), vu.end(), [&](User const& a) { return a.id == u.id; });

        if (u_it == vu.end()) return 2;

        /* add product test */
        std::cout << "add product test" << std::endl;

        std::time_t t    = std::time(0);
        std::tm*    now  = std::gmtime(&t);
        std::tm*    temp = std::gmtime(&t);

        temp->tm_mday += 1;
        t = mktime(temp);

        std::tm* tomorrow = std::gmtime(&t);

        Product p;
        p.announce   = "test-announce";
        p.chat_url   = "test-chat-url.com";
        p.created_at = *now;
        p.deliver    = Deliver::not_closed;
        p.expires_at = *tomorrow;
        p.host_id    = u.id;
        p.price      = 10000;
        p.quantity   = 10;
        p.title      = "test-title";
        p.url        = "test-url.com";

        ctx.create<Product>(p);

        auto& vp = ctx.read<Product>();

        auto& p_it = std::find_if(vp.begin(), vp.end(), [&](Product const& a) {
            return p.id == a.id;
        });

        if (p_it == vp.end()) return 3;

        /* add memberproduct test */
        std::cout << "add memberproduct test" << std::endl;

        MemberProductMap mpm;
        mpm.member_id  = u.id;
        mpm.product_id = p.id;
        mpm.quantity   = 5;

        ctx.create<MemberProductMap>(mpm);

        auto& vmpm = ctx.read<MemberProductMap>();

        auto& mpm_it = std::find_if(
            vmpm.begin(), vmpm.end(), [&](MemberProductMap const& a) {
                return mpm.id == a.id;
            });

        if (mpm_it == vmpm.end()) return 4;

        /* add categoryproduct test */
        std::cout << "add categoryproduct test" << std::endl;

        CategoryProductMap cpm;
        cpm.category_id = c.id;
        cpm.product_id  = p.id;

        ctx.create<CategoryProductMap>(cpm);

        auto& vcpm = ctx.read<CategoryProductMap>();

        auto cpm_it = std::find_if(
            vcpm.begin(), vcpm.end(), [&](CategoryProductMap const& a) {
                return cpm.id == a.id;
            });

        if (cpm_it == vcpm.end()) return 5;

        std::cout << "add test end" << std::endl;

        /* update test */



        /* remove test */

        /* remove categoryproduct test*/
        std::cout << "remove categoryproduct test" << std::endl;

        if (!ctx.remove<CategoryProductMap>(cpm_it->id)) { return 2; }

        cpm_it = std::find_if(
            vcpm.begin(), vcpm.end(), [&](CategoryProductMap const& a) {
                return a.id == cpm.id;
            });

        if (cpm_it != vcpm.end()) return 4;

        /* remove memberproduct test*/
        std::cout << "remove memberproduct test" << std::endl;

        if (!ctx.remove<MemberProductMap>(mpm_it->id)) { return 2; }

        mpm_it = std::find_if(
            vmpm.begin(), vmpm.end(), [&](MemberProductMap const& a) {
                return a.id == mpm.id;
            });

        if (mpm_it != vmpm.end()) return 4;

        /* remove category test*/
        std::cout << "remove category test" << std::endl;

        if (!ctx.remove<Category>(c_it->id)) { return 2; }

        c_it = std::find_if(vc.begin(), vc.end(), [&](Category const& a) {
            return a.id == c.id;
        });

        if (c_it != vc.end()) return 4;

        /* remove product test*/
        std::cout << "remove product test" << std::endl;

        if (!ctx.remove<Product>(p_it->id)) { return 2; }

        p_it = std::find_if(vp.begin(), vp.end(), [&](Product const& a) {
            return a.id == p.id;
        });

        if (p_it != vp.end()) return 4;

        /* remove user test*/
        std::cout << "remove user test" << std::endl;

        if (!ctx.remove<User>(u_it->id)) { return 2; }

        u_it = std::find_if(
            vu.begin(), vu.end(), [&](User const& a) { return a.id == u.id; });

        if (u_it != vu.end()) return 4;

        std::cout << "remove test end" << std::endl;
    }
    catch (sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
#include "get-products-query.h"

#include "category.h"
#include "db-context.h"
#include "product.h"

#include <algorithm>
#include <math.h>
template <>
struct ActionHandler<GetProductsQuery>::Impl
{
    DbContext& ctx;
    Impl(DbContext& ctx) : ctx(ctx) {}
};
template <>
ActionHandler<GetProductsQuery>::ActionHandler(DependencyInjection& di) :
    pImpl { std::make_unique<Impl>(di.get_service<DbContext>()) }
{}

template <>
ActionHandler<GetProductsQuery>::~ActionHandler()
{}

template <>
std::vector<ProductView>
ActionHandler<GetProductsQuery>::operator()(GetProductsQuery const& action)
{

    auto const& cpm        = pImpl->ctx.read<CategoryProductMap>();
    auto const& products   = pImpl->ctx.read<Product>();
    auto const& mpm        = pImpl->ctx.read<MemberProductMap>();
    auto const& categories = pImpl->ctx.read<Category>();

    std::vector<ProductView> product_views;
    for (auto& product : products)
    {
        ProductView pv;
        pv.id         = product.id;
        pv.title      = product.title;
        pv.expires_at = product.expires_at;
        pv.piece      = product.quantity;
        auto mpm_it
            = std::find_if(mpm.begin(), mpm.end(), [&](auto const& mpm_item) {
                  return mpm_item.member_id == action.user_id
                         && mpm_item.product_id == product.id;
              });

        if (product.host_id == action.user_id)
        { pv.member_state = member_state::host; }
        else if (mpm_it != mpm.end())
        {
            pv.member_state = member_state::nonhost;
        }
        else
        {
            pv.member_state = member_state::not_enrolled;
        }
        std::vector<MemberProductMap> filtered_mem;
        std::copy_if(mpm.begin(),
                     mpm.end(),
                     std::back_inserter(filtered_mem),
                     [&](MemberProductMap const& mpm_item) {
                         return mpm_item.product_id == product.id;
                     });
        pv.occupied_piece = 0;
        for (auto const& item : filtered_mem)
        { pv.occupied_piece += item.quantity; }
        int num_member = filtered_mem.size();

        std::vector<CategoryProductMap> filtered_cpm;
        std::copy_if(cpm.begin(),
                     cpm.end(),
                     std::back_inserter(filtered_cpm),
                     [&](CategoryProductMap const& cpm_item) {
                         return cpm_item.product_id == product.id;
                     });
        int nonhost_piece_price
            = ceil(static_cast<double>(product.price) / product.quantity / 10)
              * 10;

        std::vector<Category> filtered_cat;
        for (auto& cpm : filtered_cpm)
        {
            auto cat_it = std::find_if(
                categories.begin(), categories.end(), [&](Category const& cat) {
                    return cat.id == cpm.category_id;
                });
            filtered_cat.push_back(*cat_it);
        }

        pv.categories = filtered_cat;

        pv.piece_price = nonhost_piece_price;

        product_views.push_back(pv);
    }
    return product_views;
}
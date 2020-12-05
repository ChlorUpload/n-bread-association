#ifndef __H_GET_PRODUCTS_QUERY__
#define __H_GET_PRODUCTS_QUERY__

#include "action.h"

#include "product-view.h"

struct GetProductsQuery : public Action<std::vector<ProductView>>
{
    int user_id;
    GetProductsQuery(int user_id) : user_id { user_id } {}
};
#endif

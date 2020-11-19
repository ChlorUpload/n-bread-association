#ifndef __H_CATEGORY__
#define __H_CATEGORY__

#include <string>

struct Category
{
    int id;
    std::string name;
};

struct CategoryProductMap
{
    int id;
    int category_id;
    int product_id;
};

#endif
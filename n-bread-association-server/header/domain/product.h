#ifndef __H_PRODUCT__
#define __H_PRODUCT__

#include <string>

enum class Deliver
{
    not_closed = 0,
    preparing,
    on_deliver,
    finished
};

struct Product
{
    int         id;
    int         host_id;
    int         price;
    int         quantity;
    std::string title;
    std::string announce;
    std::string url;
    std::string chat_url;
    Deliver     deliver;
    std::tm      created_at;
    std::tm      expires_at;
    Category*   categories;
};

struct MemberProductMap
{
    int id;
    int member_id;
    int product_id;
    int quantity;
};

#endif
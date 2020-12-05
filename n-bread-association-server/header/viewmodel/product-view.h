#ifndef __H_GET_PRODUCTS_VIEW__

#define __H_GET_PRODUCTS_VIEW__

#include "category.h"
#include "date.h"
#include "view-model.h"

#include <string>
#include <vector>

enum class member_state
{
    not_enrolled = 0,
    nonhost      = 1,
    host         = 2,

};
struct ProductView : public ViewModel
{
    std::vector<Category> categories;
    int                   id;
    std::string           title;
    Date                  expires_at;
    member_state          member_state;
    int                   occupied_piece;
    int                   piece;
    int                   piece_price;

    virtual json to_json()
    {
        json res;
        json cat_json;

        for (auto& cat : categories)
        {
            json c;
            c["id"]    = cat.id;
            c["title"] = cat.name;
            cat_json.push_back(c);
        }
        res["id"]         = id;
        res["categories"] = cat_json;
        res["title"]      = title;

        res["expiresAt"]     = expires_at.to_string();
        res["memberState"]   = static_cast<int>(member_state);
        res["occupiedPiece"] = occupied_piece;
        res["piece"]         = piece;
        res["piecePrice"]    = piece_price;

        return res;
    }
};

#endif
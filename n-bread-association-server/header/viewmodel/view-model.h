#ifndef __H VIEW_MODEL__
#define __H VIEW_MODEL__

#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct ViewModel
{
    virtual json to_json() = 0;
};
#endif
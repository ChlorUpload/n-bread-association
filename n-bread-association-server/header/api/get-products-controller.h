#ifndef __H_GET_PRODUCTS_CONTROLLER__
#define __H_GET_PRODUCTS_CONTROLLER__
#include "action-manager.h"
#include "controller.h"
#include "get-products-query.h"

#include <sstream>

class GetProductsController : public Controller
{
  public:
    using Controller::Controller;
    virtual ControllerResp get_response(
        std::unordered_map<std::string, std::string> const& params) override
    {
        std::cout << "get-products-controller" << std::endl;
        auto user_it = params.find("userId");
        if (user_it == params.end())

        {

            json           json = {};
            ControllerResp cr { ControllerResp::res_status::failed,
                                ControllerResp::failure_code::invalid_argument,
                                "one or more arguments are missing",
                                json };
            return cr;
        }
        else
        {
            auto user_id_str = user_it->second;
            int  user_id;

            std::stringstream ss(user_id_str);
            ss >> user_id;
            if (ss.fail())
            {
                json           json = {};
                ControllerResp cr {
                    ControllerResp::res_status::failed,
                    ControllerResp::failure_code::invalid_argument,
                    "user_id is not a number",
                    json
                };

                return cr;
            }

            auto& pvs = _am(GetProductsQuery(user_id));
            json  ret = json::array();
            for (auto& pv : pvs) { ret.push_back(pv.to_json()); }

            ControllerResp cr { ControllerResp::res_status::success,
                                ControllerResp::failure_code::ok,
                                "success",
                                ret };
            return cr;
        }
    }
    virtual std::string get_name() override
    {

        return "getProducts";
    }
};

#endif

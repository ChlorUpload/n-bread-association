#ifndef __H_GET_PRODUCTS_CONTROLLER__
#define __H_GET_PRODUCTS_CONTROLLER__
#include "action-manager.h"
#include "controller.h"
class GetProductsController : public Controller
{
  public:
    using Controller::Controller;
    virtual ControllerResp
    get_response(std::unordered_map<std::string, std::string> const&params) override
    {



        json           json = {};
        ControllerResp cr { ControllerResp::res_status::failed,
                            ControllerResp::failure_code::invalid_argument,
                            "one or more arguments are missing",
                            json };
        return cr;
    }

        virtual std::string get_name() override
    {
        return "getProducts";
    }
};

#endif

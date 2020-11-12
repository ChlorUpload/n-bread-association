#ifndef __H_CONTROLLER__
#define __H_CONTROLLER__

#include "action-manager.h"

class Controller
{
  private:
    ActionManager& _am;

  public:
    Controller(ActionManager& am) : _am { am } {}

    virtual std::string
    get_response(std::unordered_map<std::string, std::string> params)
        = 0;

    virtual std::string get_name() = 0;
};

#endif
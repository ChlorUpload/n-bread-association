#ifndef __H_ACTION__
#define __H_ACTION__

#include "dependency-injection.h"

template <typename T>
struct Action
{
    using ReturnType = T;
};

class ActionHandlerBase
{ };

template <typename ActionT>
class ActionHandler : public ActionHandlerBase
{
    struct Impl;
    std::unique_ptr<Impl> pImpl;

public:
    ActionHandler(DependencyInjection& di);
    ~ActionHandler();

    typename ActionT::ReturnType operator()(ActionT const& action);
};

#endif
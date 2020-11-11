#ifndef __H_ACTION__
#define __H_ACTION__

#include "db-context.h"

template <typename T>
struct Action
{
    using ReturnType = T;
};

class ActionHandlerBase
{
    DbContext* _ctx;

public:
    ActionHandlerBase(DbContext* ctx)
        : _ctx{ctx}
    { }
};

template <typename ActionT>
class ActionHandler : public ActionHandlerBase
{
public:
    using ActionHandlerBase::ActionHandlerBase;

    typename ActionT::ReturnType operator()(ActionT const& action);
};

#endif
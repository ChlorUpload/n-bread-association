#ifndef __H_ACTION_MANAGER__
#define __H_ACTION_MANAGER__

#include <memory>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

#include "action.h"
#include "count-command.h"
#include "db-context.h"

class ActionManager
{
    DbContext* _ctx;

    std::unordered_map<std::type_index, std::unique_ptr<ActionHandlerBase>>
        handlers;

public:

    ActionManager() = delete;
    ActionManager(DbContext* ctx)
        : _ctx{ctx}
    { }

    template <typename ActionT>
    typename ActionT::ReturnType operator()(ActionT const& action)
    {
        static_assert(
            std::is_base_of_v<Action<typename ActionT::ReturnType>, ActionT>,
            "ActionT must be derived from Action<T>");

        auto it = handlers.find(std::type_index{typeid(ActionT)});
        if(it == handlers.end())
        {
            it = handlers
                     .insert(std::make_pair(
                         std::type_index{typeid(ActionT)},
                         std::make_unique<ActionHandler<ActionT>>(_ctx)))
                     .first;
        }

        static_cast<ActionHandler<ActionT>*>(it->second.get())
            ->
            operator()(action);
    }
};

#endif

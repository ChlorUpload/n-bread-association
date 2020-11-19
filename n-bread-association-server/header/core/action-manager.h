#ifndef __H_ACTION_MANAGER__
#define __H_ACTION_MANAGER__

#include "action.h"
#include "dependency-injection.h"

#include <memory>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

/// <summary>
/// 액션 핸들러를 저장하고, 들어온 액션 인스턴스에 맞게 액션 핸들러를
/// 실행시켜주는 클래스
/// </summary>
class ActionManager
{
    // DependencyInjection의 레퍼런스를 가지고 있다가 액션 핸들러에게 넘겨 주어
    // 각 액션 핸들러가 필요로 하는 서비스를 DependencyInjection으로부터 받아올
    // 수 있도록 합니다.
    DependencyInjection& _di;

    // 액션 핸들러를 저장합니다.
    std::unordered_map<std::type_index, std::unique_ptr<ActionHandlerBase>>
        _handlers;

  public:
    ActionManager() = delete;
    ActionManager(DependencyInjection& di) : _di { di } {}

    /// <summary>
    /// 액션 인스턴스를 넘겨 그에 맞는 액션 핸들러에 그 인스턴스를 넘기면서
    /// 실행시킵니다.
    /// </summary>
    /// <typeparam name="ActionT">액션</typeparam>
    /// <param name="action">액션 인스턴스</param>
    /// <returns>액션 핸들러가 반환한 값</returns>
    template <typename ActionT>
    typename ActionT::ReturnType operator()(ActionT const& action)
    {
        // 넘어온 템플릿 인수가 액션이 아닐 경우 assert
        static_assert(
            std::is_base_of_v<Action<typename ActionT::ReturnType>, ActionT>,
            "ActionT must be derived from Action<T>");

        // 주어진 액션에 대한 액션 핸들러가 존재하면 이를 찾고 그렇지 않다면
        // 새로 만들어서 <c>_handlers</c>에 넣습니다.
        auto it = _handlers.find(std::type_index { typeid(ActionT) });
        if (it == _handlers.end())
        {
            std::tie(it, std::ignore) = _handlers.insert(
                std::make_pair(std::type_index { typeid(ActionT) },
                               std::make_unique<ActionHandler<ActionT>>(_di)));
        }

        // 핸들러를 받아 와서 그 핸들러에 액션 인스턴스를 넘기고 실행시킵니다.
        // 또한 핸들러가 반환한 값을 반환합니다.
        return static_cast<ActionHandler<ActionT>*>(it->second.get())
            ->
            operator()(action);
    }
};

#endif

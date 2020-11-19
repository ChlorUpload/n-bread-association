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
/// �׼� �ڵ鷯�� �����ϰ�, ���� �׼� �ν��Ͻ��� �°� �׼� �ڵ鷯��
/// ��������ִ� Ŭ����
/// </summary>
class ActionManager
{
    // DependencyInjection�� ���۷����� ������ �ִٰ� �׼� �ڵ鷯���� �Ѱ� �־�
    // �� �׼� �ڵ鷯�� �ʿ�� �ϴ� ���񽺸� DependencyInjection���κ��� �޾ƿ�
    // �� �ֵ��� �մϴ�.
    DependencyInjection& _di;

    // �׼� �ڵ鷯�� �����մϴ�.
    std::unordered_map<std::type_index, std::unique_ptr<ActionHandlerBase>>
        _handlers;

  public:
    ActionManager() = delete;
    ActionManager(DependencyInjection& di) : _di { di } {}

    /// <summary>
    /// �׼� �ν��Ͻ��� �Ѱ� �׿� �´� �׼� �ڵ鷯�� �� �ν��Ͻ��� �ѱ�鼭
    /// �����ŵ�ϴ�.
    /// </summary>
    /// <typeparam name="ActionT">�׼�</typeparam>
    /// <param name="action">�׼� �ν��Ͻ�</param>
    /// <returns>�׼� �ڵ鷯�� ��ȯ�� ��</returns>
    template <typename ActionT>
    typename ActionT::ReturnType operator()(ActionT const& action)
    {
        // �Ѿ�� ���ø� �μ��� �׼��� �ƴ� ��� assert
        static_assert(
            std::is_base_of_v<Action<typename ActionT::ReturnType>, ActionT>,
            "ActionT must be derived from Action<T>");

        // �־��� �׼ǿ� ���� �׼� �ڵ鷯�� �����ϸ� �̸� ã�� �׷��� �ʴٸ�
        // ���� ���� <c>_handlers</c>�� �ֽ��ϴ�.
        auto it = _handlers.find(std::type_index { typeid(ActionT) });
        if (it == _handlers.end())
        {
            std::tie(it, std::ignore) = _handlers.insert(
                std::make_pair(std::type_index { typeid(ActionT) },
                               std::make_unique<ActionHandler<ActionT>>(_di)));
        }

        // �ڵ鷯�� �޾� �ͼ� �� �ڵ鷯�� �׼� �ν��Ͻ��� �ѱ�� �����ŵ�ϴ�.
        // ���� �ڵ鷯�� ��ȯ�� ���� ��ȯ�մϴ�.
        return static_cast<ActionHandler<ActionT>*>(it->second.get())
            ->
            operator()(action);
    }
};

#endif

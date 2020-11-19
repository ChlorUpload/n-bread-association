#ifndef __H_ACTION__
#define __H_ACTION__

#include "dependency-injection.h"

/// <summary>
/// �׼��� ���̽� Ŭ����. ��� �׼��� �� Ŭ������ ����մϴ�.
/// </summary>
/// <typeparam name="T">�׼� �ڵ鷯�� ����� �� ��ȯ�� Ÿ��</typeparam>
template <typename T>
struct Action
{
    using ReturnType = T;
};

/// <summary>
/// �׼� �ڵ鷯�� ���̽� Ŭ����. ��� �׼� �ڵ鷯�� �� Ŭ������ ����մϴ�.
/// </summary>
class ActionHandlerBase
{};

/// <summary>
/// �׼� �ڵ鷯 Ŭ����. �׼ǿ� ���� �� �׼� �ڵ鷯 Ŭ������ ���ø� Ư��ȭ�ؼ� ��
/// �׼ǿ� ���� �ڵ鷯�� ������ �� �ֽ��ϴ�.
/// </summary>
/// <typeparam name="ActionT">�׼�</typeparam>
template <typename ActionT>
class ActionHandler : public ActionHandlerBase
{
    /// <summary>
    /// pImpl idiom. �� �׼ǿ� ���� �ڵ鷯�� DependencyInjection���κ���
    /// �޾ƿͼ� ����� ������ ���۷����� �� ����ü�� �� �׼ǿ� ����
    /// Ư��ȭ�Ͽ� �� �ȿ� �����մϴ�.
    /// </summary>
    struct Impl;
    std::unique_ptr<Impl> pImpl;

  public:
    ActionHandler(DependencyInjection& di);
    ~ActionHandler();

    /// <summary>
    /// �׼� �ڵ鷯�� ����Ǵ� �κ��Դϴ�. ���⿡ ��� �ھ� ������ ���ϴ�.
    /// </summary>
    /// <param name="action">����� �׼� �ν��Ͻ�</param>
    /// <returns>�׼ǿ� �̹� ��õǾ� �ִ� ���� Ÿ�Կ� ���߾� �ʿ��� ������
    /// ��ȯ�մϴ�.</returns>
    typename ActionT::ReturnType operator()(ActionT const& action);
};

#endif
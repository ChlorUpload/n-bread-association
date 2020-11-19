#ifndef __H_ACTION__
#define __H_ACTION__

#include "dependency-injection.h"

/// <summary>
/// 액션의 베이스 클래스. 모든 액션은 이 클래스를 상속합니다.
/// </summary>
/// <typeparam name="T">액션 핸들러가 실행된 후 반환할 타입</typeparam>
template <typename T>
struct Action
{
    using ReturnType = T;
};

/// <summary>
/// 액션 핸들러의 베이스 클래스. 모든 액션 핸들러는 이 클래스를 상속합니다.
/// </summary>
class ActionHandlerBase
{};

/// <summary>
/// 액션 핸들러 클래스. 액션에 대해 이 액션 핸들러 클래스를 템플릿 특수화해서 각
/// 액션에 대한 핸들러를 구현할 수 있습니다.
/// </summary>
/// <typeparam name="ActionT">액션</typeparam>
template <typename ActionT>
class ActionHandler : public ActionHandlerBase
{
    /// <summary>
    /// pImpl idiom. 각 액션에 대한 핸들러가 DependencyInjection으로부터
    /// 받아와서 사용할 서비스의 레퍼런스를 이 구조체를 각 액션에 대해
    /// 특수화하여 그 안에 저장합니다.
    /// </summary>
    struct Impl;
    std::unique_ptr<Impl> pImpl;

  public:
    ActionHandler(DependencyInjection& di);
    ~ActionHandler();

    /// <summary>
    /// 액션 핸들러가 실행되는 부분입니다. 여기에 모든 코어 로직이 들어갑니다.
    /// </summary>
    /// <param name="action">실행될 액션 인스턴스</param>
    /// <returns>액션에 이미 명시되어 있는 리턴 타입에 맞추어 필요한 정보를
    /// 반환합니다.</returns>
    typename ActionT::ReturnType operator()(ActionT const& action);
};

#endif
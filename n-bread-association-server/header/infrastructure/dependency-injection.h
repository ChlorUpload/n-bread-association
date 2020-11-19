#ifndef __H_DEPENDENCY_INJECTION__
#define __H_DEPENDENCY_INJECTION__

#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <vector>

#pragma region Entries

/*
    객체지향 프로그래밍 수업 김찬중 튜터님의 도움을 받았습니다.
*/

template <typename T>
using RemoveAll = std::remove_const_t<std::remove_reference_t<T>>;

struct Entry
{
  private:
    void*                       _data;
    std::function<void*(void*)> _copier;
    std::function<void(void*)>  _deleter;

  public:
    Entry() : _data { nullptr } {}

    template <typename T,
              std::enable_if_t<!std::is_same_v<RemoveAll<T>, Entry>, int> = 0>
    Entry(T&& t) :
        _data { new RemoveAll<T> { std::forward<T>(t) } },
        _copier { [](void* data) {
            return new RemoveAll<T> { std::forward<T>(
                *reinterpret_cast<RemoveAll<T>*>(data)) };
        } },
        _deleter { [](void* data) {
            delete reinterpret_cast<RemoveAll<T>*>(data);
        } }
    {}

    Entry(const Entry& entry) :
        _data { entry._copier(entry._data) },
        _copier { entry._copier },
        _deleter { entry._deleter }
    {}

    ~Entry()
    {
        _deleter(_data);
    }

  public:
    template <typename T>
    T& Get()
    {
        return *reinterpret_cast<T*>(_data);
    }

    template <typename T>
    T const& Get() const
    {
        return *reinterpret_cast<T*>(_data);
    }
};

template <typename T>
std::pair<std::type_index, Entry> MakeKeyValuePair(T&& t)
{
    using RemovedT = RemoveAll<T>;
    return std::make_pair(std::type_index { typeid(RemovedT) },
                          Entry { std::forward<T&&>(t) });
}

template <typename T>
T const&
GetFromEntries(std::unordered_map<std::type_index, Entry> const& entries)
{
    return entries.at(std::type_index { typeid(T) }).Get<T>();
}

template <typename T, typename TupleT, std::size_t... Indices>
T Construct(TupleT&& tuple, std::index_sequence<Indices...>)
{
    return T { std::get<Indices>(std::forward<TupleT>(tuple))... };
}

template <typename TupleT, std::size_t... Indices>
TupleT ConstructTupleFromEntries(
    std::unordered_map<std::type_index, Entry> const& entries,
    std::index_sequence<Indices...>)
{
    return std::make_tuple(
        GetFromEntries<std::tuple_element_t<Indices, TupleT>>(entries)...);
}

template <typename T>
T ConstructFromEntries(
    std::unordered_map<std::type_index, Entry> const& entries)
{
    using ParamType = typename T::ParamType;

    auto idxSequence
        = std::make_index_sequence<std::tuple_size_v<ParamType>> {};
    ParamType tup = ConstructTupleFromEntries<ParamType>(entries, idxSequence);
    return Construct<T>(std::move(tup), idxSequence);
}

#pragma endregion

/// <summary>
/// ASP.NET Core의 DependencyInjection을 참고해서 만든 클래스. 싱글톤 패턴을
/// 사용하지 않고 한 개의 인스턴스로 서비스를 관리하며, 서비스들을 액션 핸들러
/// 등의 로직을 처리하는 객체에서 쉽게 받아올 수 있도록 도와주는 역할을 합니다.
/// </summary>
class DependencyInjection
{
  private:
    /// <summary>
    /// 어떤 서비스라도 저장할 수 있는 객체
    /// </summary>
    std::unordered_map<std::type_index, Entry> entries;

  public:
    /// <summary>
    /// 템플릿 인수로 들어온 서비스 인스턴스를 반환합니다.
    /// </summary>
    /// <typeparam name="ServiceT">사용할 서비스</typeparam>
    /// <returns>서비스 인스턴스</returns>
    template <typename ServiceT>
    ServiceT& get_service()
    {
        // 서비스 인스턴스를 가지고 있는지 확인해서 있다면 이를 반환하고 그렇지
        // 않다면 새로 인스턴스를 생성해서 반환합니다.
        auto it = entries.find(std::type_index { typeid(ServiceT) });
        if (it == entries.end())
        {
            std::tie(it, std::ignore)
                = entries.insert(MakeKeyValuePair(ServiceT {}));
        }

        return it->second.Get<ServiceT>();
    }
};

#endif
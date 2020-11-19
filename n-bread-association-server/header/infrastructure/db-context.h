#ifndef __H_DB_CONTEXT__
#define __H_DB_CONTEXT__

#include "category.h"
#include "product.h"
#include "user.h"

#include <iostream>
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/prepared_statement.h>
#include <jdbc/mysql_connection.h>
#include <jdbc/mysql_driver.h>
#include <memory>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <vector>

/// <summary>
/// 모델의 포워드 이터레이터
/// </summary>
/// <typeparam name="T">모델 타입</typeparam>
template <typename T>
class Iterator
{
  public:
    using iterator_category = std::forward_iterator_tag;
    using value_type        = T;
    using difference_type   = std::ptrdiff_t;
    using pointer           = T*;
    using reference         = T&;

  private:
    T                               _val;
    std::shared_ptr<sql::ResultSet> _result;

    void get_value();

  public:
    Iterator(sql::ResultSet* result = nullptr) : _result { result }
    {
        if (result != nullptr)
        {
            if (result->next()) { get_value(); }
        }
    }

    Iterator(Iterator const& it) = default;
    Iterator& operator=(Iterator const& it) = default;

    T& operator*()
    {
        return _val;
    }
    T* operator->()
    {
        return &_val;
    }
    Iterator& operator++()
    {
        if (!_result->next()) { _result = nullptr; }
        else
        {
            get_value();
        }
        return *this;
    }
    Iterator operator++(int)
    {
        Iterator temp = *this;
        ++*this;
        return temp;
    }

    Iterator begin()
    {
        return *this;
    }

    Iterator end()
    {
        return Iterator {};
    }

    bool operator==(Iterator const& other)
    {
        return _result == other._result;
    }

    bool operator!=(Iterator const& other)
    {
        return _result != other._result;
    }
};

/// <summary>
/// DB와 통신하는 서비스 클래스
/// </summary>
class DbContext
{
  private:
    static sql::Driver* _driver;

    std::unique_ptr<sql::Connection> _con;
    std::vector<Category>            _categories;
    std::vector<CategoryProductMap>  _cp_map;
    std::vector<Product>             _products;
    std::vector<MemberProductMap>    _mp_map;
    std::vector<User>                _users;

    /// <summary>
    /// DB를 읽어 모델에 저장하기 위한  함수.
    /// </summary>
    /// <typeparam name="T">모델 타입</typeparam>
    /// <returns>이터레이터</returns>
    template <typename T>
    Iterator<T> get();

    static sql::Driver* get_driver()
    {
        if (_driver == nullptr)
            _driver = sql::mysql::get_mysql_driver_instance();

        return _driver;
    }
    static sql::Connection* create_connection()
    {
        sql::Driver*     driver = get_driver();
        sql::Connection* con { driver->connect(
            "tcp://127.0.0.1:3306", "root", "lunarainproject!") };
        con->setSchema("nba");

        return con;
    }

    int get_last_id();

  public:
    DbContext();

    /// <summary>
    /// 모델에 저장된 값을 읽어오는 함수
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <returns></returns>
    template <typename T>
    std::vector<T> const& read();

    /// <summary>
    /// DB와 모델에 정보를 추가하는 함수. model을 채워서 넘기되, id는 비워
    /// 두세요. id가 자동으로 추가됩니다.
    /// </summary>
    /// <typeparam name="T">모델 타입</typeparam>
    /// <param name="model">모델</param>
    template <typename T>
    bool create(T& model);

    /// <summary>
    /// DB와 모델의 정보를 수정하는 함수.
    /// </summary>
    /// <typeparam name="T">모델 타입</typeparam>
    /// <param name="model">모델</param>
    template <typename T>
    bool update(T const& model);

    /// <summary>
    /// DB와 모델의 정보를 제거하는 함수.
    /// </summary>
    /// <typeparam name="T">모델 타입</typeparam>
    /// <param name="id">제거하려는 모델의 아이디</param>
    template <typename T>
    bool remove(int id);
};

#endif
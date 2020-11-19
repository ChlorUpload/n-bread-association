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
/// ���� ���ͷ�����
/// </summary>
/// <typeparam name="T">�� Ÿ��</typeparam>
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
/// DB�� ����ϴ� ���� Ŭ����
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
    /// DB�� �о� �𵨿� �����ϱ� ����  �Լ�.
    /// </summary>
    /// <typeparam name="T">�� Ÿ��</typeparam>
    /// <returns>���ͷ�����</returns>
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
    /// �𵨿� ����� ���� �о���� �Լ�
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <returns></returns>
    template <typename T>
    std::vector<T> const& read();

    /// <summary>
    /// DB�� �𵨿� ������ �߰��ϴ� �Լ�. model�� ä���� �ѱ��, id�� ���
    /// �μ���.
    /// </summary>
    /// <typeparam name="T">�� Ÿ��</typeparam>
    /// <param name="model">��</param>
    template <typename T>
    bool create(T const& model);

    /// <summary>
    /// DB�� ���� ������ �����ϴ� �Լ�.
    /// </summary>
    /// <typeparam name="T">�� Ÿ��</typeparam>
    /// <param name="model">��</param>
    template <typename T>
    bool update(T const& model);

    /// <summary>
    /// DB�� ���� ������ �����ϴ� �Լ�.
    /// </summary>
    /// <typeparam name="T">�� Ÿ��</typeparam>
    /// <param name="id">�����Ϸ��� ���� ���̵�</param>
    template <typename T>
    bool remove(int id);
};

#endif
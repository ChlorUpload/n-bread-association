#ifndef __H_DB_CONTEXT__
#define __H_DB_CONTEXT__

#include <iostream>
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/prepared_statement.h>
#include <jdbc/mysql_connection.h>
#include <jdbc/mysql_driver.h>
#include <memory>
#include <string>

class DbContext
{
  private:
    sql::Driver*                     _driver;
    std::unique_ptr<sql::Connection> _con;

  public:
    DbContext() :
        _driver { sql::mysql::get_mysql_driver_instance() },
        _con {
            _driver->connect("tcp://127.0.0.1:3306", "root", "lunarainproject!")
        }
    {
        _con->setSchema("nba");
    }

    int         get_user_id(std::string const& email);
    std::string get_user_encrypted_pw(int user_id);

    void add_user(std::string const& name,
                  std::string const& email,
                  std::string const& password,
                  std::string const& phone);
};

#endif
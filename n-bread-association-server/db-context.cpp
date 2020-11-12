#include "db-context.h"

int DbContext::get_user_id(std::string const& email)
{
    int ret = 0;

    std::unique_ptr<sql::PreparedStatement> pre_stmt { _con->prepareStatement(
        "SELECT `id` FROM `users` WHERE `email` = ?") };
    pre_stmt->setString(1, email.c_str());
    std::unique_ptr<sql::ResultSet> result { pre_stmt->executeQuery() };

    if (result->next())
    {
        int user_id = result->getInt("id");
        return user_id;
    }
    else
    {
        return -1;
    }
}

std::string DbContext::get_user_encrypted_pw(int user_id)
{
    std::unique_ptr<sql::PreparedStatement> pre_stmt { _con->prepareStatement(
        "SELECT `password` FROM `users` WHERE `id` = ?") };
    pre_stmt->setString(1, std::to_string(user_id).c_str());
    std::unique_ptr<sql::ResultSet> result { pre_stmt->executeQuery() };

    if (result->next())
    {
        const char* password = result->getString("password").c_str();
        return password;
    }
    else
    {
        return "";
    }
}

void DbContext::add_user(std::string const& name,
                         std::string const& email,
                         std::string const& password,
                         std::string const& phone)
{
    std::unique_ptr<sql::PreparedStatement> pre_stmt { _con->prepareStatement(
        "INSERT INTO `nba`.`users` (`name`, `email`, `password`, "
        "`phone`, `verified`) VALUES (?, ?, ?, ?, '0')") };

    pre_stmt->setString(1, name.c_str());
    pre_stmt->setString(2, email.c_str());
    pre_stmt->setString(3, password.c_str());
    pre_stmt->setString(4, phone.c_str());

    pre_stmt->executeUpdate();
}
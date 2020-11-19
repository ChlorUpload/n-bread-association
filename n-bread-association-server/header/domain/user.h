#ifndef __H_USER__
#define __H_USER__

#include <string>

struct User
{
    int id;
    std::string name;
    std::string email;
    std::string encrypted_pw;
    std::string phone;
    bool        verified;
};

#endif
#ifndef __H_CREDENTIALS_MANAGER__
#define __H_CREDENTIALS_MANAGER__

#define SIGNATURE_LEN 20

#include <string>

class CredentialsManager
{
  private:
    std::string       _signature  = "";
    const std::string _issuer     = "nba-auth";
    const int         _expire_sec = 20000;

  public:
    CredentialsManager();

    std::string create_token(std::string const& user_id);
    bool        verify_token(std::string const& token);
    std::string get_user_id(std::string const& token);
};

#endif
#ifndef __H_CREDENTIALS_SERVICE__
#define __H_CREDENTIALS_SERVICE__

#define SIGNATURE_LEN 20

#include <string>

class CredentialsService
{
  private:
    std::string       _signature  = "";
    const std::string _issuer     = "nba-auth";
    const int         _expire_sec = 20000;

  public:
    CredentialsService();

    std::string create_token(int user_id);
    bool        verify_token(std::string const& token);
    int         get_user_id(std::string const& token);
};

#endif
#ifndef __H_CREDENTIALS_MANAGER__
#define __H_CREDENTIALS_MANAGER__

#define SIGNATURE_LEN 20

#include "jwt-cpp/jwt.h"

#include <random>

class CredentialsManager
{
  private:
    std::string       _signature  = "";
    const std::string _issuer     = "nba-auth";
    const int         _expire_sec = 20000;

  public:
    CredentialsManager()
    {
        std::random_device rd;
        std::mt19937       gen { rd() };
        std::uniform_int_distribution<int> dis(0, 25);

        for (int i = 0; i < SIGNATURE_LEN; i++)
        {
            char rand_char = 'A' + dis(gen);
            _signature.push_back(rand_char);
        }

        //std::cout << "signature : " << _signature << std::endl;
    }

    std::string create_token(std::string const& user_id)
    {
        return jwt::create()
            .set_issuer(_issuer)
            .set_issued_at(std::chrono::system_clock::now())
            .set_expires_at(std::chrono::system_clock::now()
                            + std::chrono::seconds { _expire_sec })
            .set_type("JWS")
            .set_payload_claim("user_id", jwt::claim(user_id))
            .sign(jwt::algorithm::hs256 { _signature });
    }

    bool verify_token(std::string const& token)
    {
        auto verifier
            = jwt::verify()
                  .allow_algorithm(jwt::algorithm::hs256 { _signature })
                  .with_issuer(_issuer);

        auto decoded = jwt::decode(token);

        try
        {
            verifier.verify(decoded);
        }
        catch (...)
        {
            return false;
        }
        return true;
    }

    std::string get_user_id(std::string const& token)
    {
        auto decoded = jwt::decode(token);

        auto claim = decoded.get_payload_claim("user_id");

        return claim.as_string();
    }
};

#endif
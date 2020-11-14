#include "credentials-service.h"

#include "jwt-cpp/jwt.h"

#include <random>

CredentialsService::CredentialsService()
{
    std::random_device                 rd;
    std::mt19937                       gen { rd() };
    std::uniform_int_distribution<int> dis(0, 25);

    for (int i = 0; i < SIGNATURE_LEN; i++)
    {
        char rand_char = 'A' + dis(gen);
        _signature.push_back(rand_char);
    }

    // std::cout << "signature : " << _signature << std::endl;
}

std::string CredentialsService::create_token(int user_id)
{
    return jwt::create()
        .set_issuer(_issuer)
        .set_issued_at(std::chrono::system_clock::now())
        .set_expires_at(std::chrono::system_clock::now()
                        + std::chrono::seconds { _expire_sec })
        .set_type("JWS")
        .set_payload_claim("user_id", jwt::claim(std::to_string(user_id)))
        .sign(jwt::algorithm::hs256 { _signature });
}

bool CredentialsService::verify_token(std::string const& token)
{
    auto verifier = jwt::verify()
                        .allow_algorithm(jwt::algorithm::hs256 { _signature })
                        .with_issuer(_issuer);
  
    try
    {
        auto decoded = jwt::decode(token);
        verifier.verify(decoded);
    }
    catch (...)
    {
        return false;
    }
    return true;
}

int CredentialsService::get_user_id(std::string const& token)
{
    int ret = 0;
    
    try
    {  
        auto decoded = jwt::decode(token);
        auto claim = decoded.get_payload_claim("user_id");
        ret = std::atoi(claim.as_string().c_str());
    }
    catch (...)
    {
        return -1;
    }

    return ret;
}
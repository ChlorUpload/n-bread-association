#ifndef __H_ENCRYPTION_SERVICE__
#define __H_ENCRYPTION_SERVICE__

#include <string>
#include <openssl/sha.h>

class EncryptionService
{
  private:
    SHA256_CTX  _sha256_ctx;
    std::string _sha256(std::string const& str);

  public:
    std::string encrypt(std::string const& str);
};

#endif
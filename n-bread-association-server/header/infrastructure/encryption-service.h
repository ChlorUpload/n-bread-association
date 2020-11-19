#ifndef __H_ENCRYPTION_SERVICE__
#define __H_ENCRYPTION_SERVICE__

#include <string>
#include <openssl/sha.h>

/// <summary>
/// 암호화를 수행하는 클래스
/// </summary>
class EncryptionService
{
  private:
    /// <summary>
    /// SHA256 알고리즘을 이용해 주어진 문자열을 암호화
    /// </summary>
    SHA256_CTX  _sha256_ctx;
    std::string _sha256(std::string const& str);

  public:
    /// <summary>
    /// 주어진 문자열을 암호화합니다.
    /// </summary>
    /// <param name="str">암호화할 문자열</param>
    /// <returns>암호화된 문자열</returns>
    std::string encrypt(std::string const& str);
};

#endif
#ifndef __H_ENCRYPTION_SERVICE__
#define __H_ENCRYPTION_SERVICE__

#include <string>
#include <openssl/sha.h>

/// <summary>
/// ��ȣȭ�� �����ϴ� Ŭ����
/// </summary>
class EncryptionService
{
  private:
    /// <summary>
    /// SHA256 �˰����� �̿��� �־��� ���ڿ��� ��ȣȭ
    /// </summary>
    SHA256_CTX  _sha256_ctx;
    std::string _sha256(std::string const& str);

  public:
    /// <summary>
    /// �־��� ���ڿ��� ��ȣȭ�մϴ�.
    /// </summary>
    /// <param name="str">��ȣȭ�� ���ڿ�</param>
    /// <returns>��ȣȭ�� ���ڿ�</returns>
    std::string encrypt(std::string const& str);
};

#endif
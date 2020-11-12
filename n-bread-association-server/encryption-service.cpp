#include "encryption-service.h"

#include <iomanip>
#include <iostream>
#include <sstream>

std::string EncryptionService::_sha256(std::string const& str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX    sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    { ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i]; }
    return ss.str();
}

std::string EncryptionService::encrypt(std::string const& str)
{
    return _sha256(str);
}
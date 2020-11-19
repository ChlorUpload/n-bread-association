#ifndef __H_CREDENTIALS_SERVICE__
#define __H_CREDENTIALS_SERVICE__

#define SIGNATURE_LEN 20

#include <string>

/// <summary>
/// JSON 웹 토큰(jwt)을 발급하기 위한 서비스
/// </summary>
class CredentialsService
{
  private:
    /// <summary>
    /// jwt을 인증하기 위한 시그니처 키. 이는 서버가 켜질때마다 변화합니다.
    /// </summary>
    std::string _signature = "";

    /// <summary>
    /// jwt 발행자
    /// </summary>
    const std::string _issuer = "nba-auth";

    /// <summary>
    /// 토큰의 발행으로부터 만료까지의 시간 (초)
    /// </summary>
    const int _expire_sec = 20000;

  public:
    CredentialsService();

    /// <summary>
    /// 토큰을 발행합니다.
    /// </summary>
    /// <param name="user_id">유저 아이디</param>
    /// <returns>액세스 토큰</returns>
    std::string create_token(int user_id);

    /// <summary>
    /// 토큰이 유효한지 확인합니다. 이는 단순히 이 서버가 발행한 토큰인지만
    /// 확인합니다.
    /// </summary>
    /// <param name="token">액세스 토큰</param>
    /// <returns>토큰의 유효 여부</returns>
    bool verify_token(std::string const& token);

    /// <summary>
    /// 액세스 토큰을 해석해서 유저 아이디를 받아옵니다.
    /// </summary>
    /// <param name="token">액세스 토큰</param>
    /// <returns>유저 아이디</returns>
    int  get_user_id(std::string const& token);
};

#endif
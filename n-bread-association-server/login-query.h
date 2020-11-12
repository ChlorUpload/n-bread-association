#ifndef __H_LOGIN_QUERY__
#define __H_LOGIN_QUERY__

#include "action.h"

#include <string>

/// <summary>
/// 로그인 상태를 나타내는 열거형
/// </summary>
enum class LoginState
{
    /// <summary>
    /// 로그인 성공
    /// </summary>
    success = 0,

    /// <summary>
    /// 일치하는 이메일 없음
    /// </summary>
    no_email,

    /// <summary>
    /// 비밀번호가 일치하지 않음
    /// </summary>
    pw_mismatch
};

/// <summary>
/// 이메일과 비밀번호를 받아서 액세스 토큰을 받아오는 쿼리
/// </summary>
struct LoginQuery : Action<std::pair<LoginState, std::string>>
{
    std::string email, password;

    LoginQuery(std::string const& email, std::string const& password) :
        email { email },
        password { password }
    {}
};

#endif
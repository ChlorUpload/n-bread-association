#ifndef __H_CHECK_TOKEN_QUERY__
#define __H_CHECK_TOKEN_QUERY__

#include "action.h"

#include <string>

/// <summary>
/// AccessToken이 유효한지 확인하는 쿼리
/// </summary>
struct CheckTokenQuery : Action<bool>
{
    /// <summary>
    /// 액세스 토큰
    /// </summary>
    std::string access_token;

    CheckTokenQuery(std::string const& access_token) :
        access_token { access_token }
    {}
};

#endif
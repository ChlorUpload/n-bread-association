#ifndef __H_CHECK_TOKEN_QUERY__
#define __H_CHECK_TOKEN_QUERY__

#include "action.h"

#include <string>

/// <summary>
/// AccessToken�� ��ȿ���� Ȯ���ϴ� ����
/// </summary>
struct CheckTokenQuery : Action<bool>
{
    std::string access_token;

    CheckTokenQuery(std::string const& access_token) :
        access_token { access_token }
    {}
};

#endif
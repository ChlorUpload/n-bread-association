#ifndef __H_LOGIN_QUERY__
#define __H_LOGIN_QUERY__

#include "action.h"

#include <string>

/// <summary>
/// �α��� ���¸� ��Ÿ���� ������
/// </summary>
enum class LoginState
{
    /// <summary>
    /// �α��� ����
    /// </summary>
    success = 0,

    /// <summary>
    /// ��ġ�ϴ� �̸��� ����
    /// </summary>
    no_email,

    /// <summary>
    /// ��й�ȣ�� ��ġ���� ����
    /// </summary>
    pw_mismatch
};

/// <summary>
/// �̸��ϰ� ��й�ȣ�� �޾Ƽ� �׼��� ��ū�� �޾ƿ��� ����
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
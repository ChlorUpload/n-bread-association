#ifndef __H_USER__
#define __H_USER__

#include <string>

/// <summary>
/// ���� ������ ��� Ŭ����
/// </summary>
struct User
{
    int id;

    /// <summary>
    /// ������ �̸�
    /// </summary>
    std::string name;

    /// <summary>
    /// ������ �̸��� �ּ�. �ݵ�� dgist.ac.kr�̾�� ��.
    /// </summary>
    std::string email;
    
    /// <summary>
    /// ������ ��ȣȭ�� ��й�ȣ
    /// </summary>
    std::string encrypted_pw;

    /// <summary>
    /// ������ �ڵ��� ��ȣ
    /// </summary>
    std::string phone;

    /// <summary>
    /// ������ ������Ʈ ������ Ȯ�� ����
    /// </summary>
    bool        verified;
};

#endif
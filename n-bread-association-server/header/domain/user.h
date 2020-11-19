#ifndef __H_USER__
#define __H_USER__

#include <string>

/// <summary>
/// 유저 정보를 담는 클래스
/// </summary>
struct User
{
    int id;

    /// <summary>
    /// 유저의 이름
    /// </summary>
    std::string name;

    /// <summary>
    /// 유저의 이메일 주소. 반드시 dgist.ac.kr이어야 함.
    /// </summary>
    std::string email;
    
    /// <summary>
    /// 유저의 암호화된 비밀번호
    /// </summary>
    std::string encrypted_pw;

    /// <summary>
    /// 유저의 핸드폰 번호
    /// </summary>
    std::string phone;

    /// <summary>
    /// 유저의 디지스트 구성원 확인 여부
    /// </summary>
    bool        verified;
};

#endif
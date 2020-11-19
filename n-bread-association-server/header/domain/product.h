#ifndef __H_PRODUCT__
#define __H_PRODUCT__

#include <string>

/// <summary>
/// 배송 상태를 나타내는 열거형
/// </summary>
enum class Deliver
{
    /// <summary>
    /// 모짐이 마감되지 않음
    /// </summary>
    not_closed = 0,
    /// <summary>
    /// 배송 준비 중
    /// </summary>
    preparing,
    /// <summary>
    /// 배송중
    /// </summary>
    on_deliver,
    /// <summary>
    /// 배송 완료
    /// </summary>
    finished
};

/// <summary>
/// 상품의 정보를 담는 클래스
/// </summary>
struct Product
{
    int id;

    /// <summary>
    /// 상품의 호스트 아이디
    /// </summary>
    int         host_id;

    /// <summary>
    /// 상품 전체 가격
    /// </summary>
    int         price;

    /// <summary>
    /// 상품의 낱개 개수
    /// </summary>
    int         quantity;

    /// <summary>
    /// 상품 제목
    /// </summary>
    std::string title;

    /// <summary>
    /// 상품의 공지사항
    /// </summary>
    std::string announce;

    /// <summary>
    /// 상품 정보를 볼 수 있는 URL
    /// </summary>
    std::string url;

    /// <summary>
    /// 상품을 구매할 사람들끼리 대화할 수 있는 채팅방 URL
    /// </summary>
    std::string chat_url;
    
    /// <summary>
    /// 상품의 배송 상태
    /// </summary>
    Deliver     deliver;

    /// <summary>
    /// 상품이 등록된 시간 (그리니치 천문대 기준)
    /// </summary>
    std::tm     created_at;

    /// <summary>
    /// 상품 모집 마감 기한 (그리니치 천문대 기준)
    /// </summary>
    std::tm     expires_at;
};

/// <summary>
/// 상품을 구매할 유저와 상품 간의 연결을 나타내는 클래스
/// </summary>
struct MemberProductMap
{
    int id;

    /// <summary>
    /// 상품을 구매하는 유저(멤버)의 아이디
    /// </summary>
    int member_id;

    /// <summary>
    /// 상품의 아이디
    /// </summary>
    int product_id;

    /// <summary>
    /// 이 상품을 구매하는 유저(멤버)가 구매하는 낱개 수량
    /// </summary>
    int quantity;
};

#endif
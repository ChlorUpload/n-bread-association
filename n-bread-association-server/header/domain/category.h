#ifndef __H_CATEGORY__
#define __H_CATEGORY__

#include <string>

/// <summary>
/// 카테고리를 담는 클래스
/// </summary>
struct Category
{
    int id;

    /// <summary>
    /// 카테고리 이름
    /// </summary>
    std::string name;
};

/// <summary>
/// 카테고리와 상품의 연결 정보를 나타내는 클래스
/// </summary>
struct CategoryProductMap
{
    int id;

    /// <summary>
    /// 카테고리 아이디
    /// </summary>
    int category_id;
    
    /// <summary>
    /// 상품 아이디
    /// </summary>
    int product_id;
};

#endif
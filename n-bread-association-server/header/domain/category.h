#ifndef __H_CATEGORY__
#define __H_CATEGORY__

#include <string>

/// <summary>
/// ī�װ��� ��� Ŭ����
/// </summary>
struct Category
{
    int id;

    /// <summary>
    /// ī�װ� �̸�
    /// </summary>
    std::string name;
};

/// <summary>
/// ī�װ��� ��ǰ�� ���� ������ ��Ÿ���� Ŭ����
/// </summary>
struct CategoryProductMap
{
    int id;

    /// <summary>
    /// ī�װ� ���̵�
    /// </summary>
    int category_id;
    
    /// <summary>
    /// ��ǰ ���̵�
    /// </summary>
    int product_id;
};

#endif
#ifndef __H_PRODUCT__
#define __H_PRODUCT__

#include <string>

/// <summary>
/// ��� ���¸� ��Ÿ���� ������
/// </summary>
enum class Deliver
{
    /// <summary>
    /// ������ �������� ����
    /// </summary>
    not_closed = 0,
    /// <summary>
    /// ��� �غ� ��
    /// </summary>
    preparing,
    /// <summary>
    /// �����
    /// </summary>
    on_deliver,
    /// <summary>
    /// ��� �Ϸ�
    /// </summary>
    finished
};

/// <summary>
/// ��ǰ�� ������ ��� Ŭ����
/// </summary>
struct Product
{
    int id;

    /// <summary>
    /// ��ǰ�� ȣ��Ʈ ���̵�
    /// </summary>
    int         host_id;

    /// <summary>
    /// ��ǰ ��ü ����
    /// </summary>
    int         price;

    /// <summary>
    /// ��ǰ�� ���� ����
    /// </summary>
    int         quantity;

    /// <summary>
    /// ��ǰ ����
    /// </summary>
    std::string title;

    /// <summary>
    /// ��ǰ�� ��������
    /// </summary>
    std::string announce;

    /// <summary>
    /// ��ǰ ������ �� �� �ִ� URL
    /// </summary>
    std::string url;

    /// <summary>
    /// ��ǰ�� ������ ����鳢�� ��ȭ�� �� �ִ� ä�ù� URL
    /// </summary>
    std::string chat_url;
    
    /// <summary>
    /// ��ǰ�� ��� ����
    /// </summary>
    Deliver     deliver;

    /// <summary>
    /// ��ǰ�� ��ϵ� �ð� (�׸���ġ õ���� ����)
    /// </summary>
    std::tm     created_at;

    /// <summary>
    /// ��ǰ ���� ���� ���� (�׸���ġ õ���� ����)
    /// </summary>
    std::tm     expires_at;
};

/// <summary>
/// ��ǰ�� ������ ������ ��ǰ ���� ������ ��Ÿ���� Ŭ����
/// </summary>
struct MemberProductMap
{
    int id;

    /// <summary>
    /// ��ǰ�� �����ϴ� ����(���)�� ���̵�
    /// </summary>
    int member_id;

    /// <summary>
    /// ��ǰ�� ���̵�
    /// </summary>
    int product_id;

    /// <summary>
    /// �� ��ǰ�� �����ϴ� ����(���)�� �����ϴ� ���� ����
    /// </summary>
    int quantity;
};

#endif
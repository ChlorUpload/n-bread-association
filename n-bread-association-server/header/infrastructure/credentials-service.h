#ifndef __H_CREDENTIALS_SERVICE__
#define __H_CREDENTIALS_SERVICE__

#define SIGNATURE_LEN 20

#include <string>

/// <summary>
/// JSON �� ��ū(jwt)�� �߱��ϱ� ���� ����
/// </summary>
class CredentialsService
{
  private:
    /// <summary>
    /// jwt�� �����ϱ� ���� �ñ״�ó Ű. �̴� ������ ���������� ��ȭ�մϴ�.
    /// </summary>
    std::string _signature = "";

    /// <summary>
    /// jwt ������
    /// </summary>
    const std::string _issuer = "nba-auth";

    /// <summary>
    /// ��ū�� �������κ��� ��������� �ð� (��)
    /// </summary>
    const int _expire_sec = 20000;

  public:
    CredentialsService();

    /// <summary>
    /// ��ū�� �����մϴ�.
    /// </summary>
    /// <param name="user_id">���� ���̵�</param>
    /// <returns>�׼��� ��ū</returns>
    std::string create_token(int user_id);

    /// <summary>
    /// ��ū�� ��ȿ���� Ȯ���մϴ�. �̴� �ܼ��� �� ������ ������ ��ū������
    /// Ȯ���մϴ�.
    /// </summary>
    /// <param name="token">�׼��� ��ū</param>
    /// <returns>��ū�� ��ȿ ����</returns>
    bool verify_token(std::string const& token);

    /// <summary>
    /// �׼��� ��ū�� �ؼ��ؼ� ���� ���̵� �޾ƿɴϴ�.
    /// </summary>
    /// <param name="token">�׼��� ��ū</param>
    /// <returns>���� ���̵�</returns>
    int  get_user_id(std::string const& token);
};

#endif
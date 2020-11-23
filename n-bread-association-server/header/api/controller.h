#ifndef __H_CONTROLLER__
#define __H_CONTROLLER__

#include "action-manager.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

/// <summary>
/// ��Ʈ�ѷ��� ���̽� Ŭ����. ��� ��Ʈ�ѷ��� �� Ŭ������ ����մϴ�.
/// </summary>
class Controller
{
  protected:
    /// <summary>
    /// ��Ʈ�ѷ��� �׼� �Ŵ������� �׼� ������ ��û�մϴ�.
    /// </summary>
    ActionManager& _am;

  public:
    /// <summary>
    /// ��Ʈ�ѷ��� ��ȯ�ϴ� Ÿ��. �������� ����, ���� �ڵ�, �α�, ������ ����
    /// JSON ��ü�� ��� Ŭ����.
    /// </summary>
    struct ControllerResp
    {
        /// <summary>
        /// ��û ����
        /// </summary>
        enum class req_status
        {
            /// <summary>
            /// ��û ����
            /// </summary>
            success = 0,
            /// <summary>
            /// ��û ����
            /// </summary>
            failed = 1,
        };

        /// <summary>
        /// ���� �ڵ�
        /// </summary>
        enum class failure_code
        {
            /// <summary>
            /// ���� (�⺻��)
            /// </summary>
            ok = 0,
            /// <summary>
            /// ���������� �μ�
            /// </summary>
            invalid_argument,
            /// <summary>
            /// �׼��� �ź�
            /// </summary>
            access_denied,
            /// <summary>
            /// �ߺ� �̸���
            /// </summary>
            duplicate_email,
            /// <summary>
            /// �� �� ���� ����
            /// </summary>
            unknown_error,
        };

        req_status   status;
        failure_code failure;
        std::string  log;
        json         response;
    };

    Controller(ActionManager& am) : _am { am } {}

    /// <summary>
    /// ��Ʈ�ѷ����� params ��ü�� �ְ� ControllerResp ��ü�� �޾ƿɴϴ�.
    /// </summary>
    /// <param name="params">���� ��Ʈ���� �º��� key��, �캯�� value�� ���� map</param>
    /// <returns></returns>
    virtual ControllerResp
    get_response(std::unordered_map<std::string, std::string> const& params)
        = 0;

    /// <summary>
    /// ��Ʈ�ѷ��� �̸��� �޾ƿɴϴ�.
    /// </summary>
    /// <returns>��Ʈ�ѷ� �̸�</returns>
    virtual std::string get_name() = 0;
};

#endif
#include "action-manager.h"
#include "check-token-controller.h"
#include "controller-manager.h"
#include "controller.h"
#include "credentials-service.h"
#include "dependency-injection.h"

int main(void)
{
    DependencyInjection di;
    ActionManager       am { di };

    CheckTokenController ctc { am };

    auto& cs = di.get_service<CredentialsService>();

    auto token = cs.create_token(12345);

    std::unordered_map<std::string, std::string> params
        = { { "accessToken", token } };

    auto res = ctc.get_response(params);

    std::cout << res.log << std::endl;

    if (res.status == Controller::ControllerResp::res_status::success)
    { return 0; }
    else
    {
        return 1;
    }
}
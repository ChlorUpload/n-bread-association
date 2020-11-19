#ifndef __H_CONTROLLER_MANAGER__
#define __H_CONTROLLER_MANAGER__

#include "action-manager.h"
#include "controller.h"

#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/config.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http  = beast::http;          // from <boost/beast/http.hpp>
namespace net   = boost::asio;          // from <boost/asio.hpp>
using tcp       = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>

class ControllerManager
{
  private:
    ActionManager&                                               _am;
    std::unordered_map<std::string, std::unique_ptr<Controller>> _controllers;

    std::unordered_map<std::string, std::string>
                                        _parse_query_str(std::string const& query_str);
    std::string                         _decode(std::string const& str);
    std::pair<std::string, std::string> _decompose(std::string const& str);

  public:
    ControllerManager(ActionManager& am) : _am { am } {}

    http::response<http::string_body>
    get_response(http::request<http::string_body>&& req);

    template <typename T>
    ControllerManager& add_controller()
    {
        static_assert(std::is_base_of_v<Controller, T>,
                      "T must be a controller");

        auto controller = std::make_unique<T>(_am);
        auto name       = controller->get_name();

        _controllers.insert(
            std::make_pair(std::move(name), std::move(controller)));

        return *this;
    }
};

#endif
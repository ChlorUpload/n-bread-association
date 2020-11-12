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
    _parse_query_str(std::string query_str)
    {
        return {};
    }

    std::pair<std::string, std::string> _decompose(std::string str)
    {
        auto question_pos = str.find('?');
        if (question_pos == std::string::npos)
        {
            return std::pair<std::string, std::string> {
                str.substr(1, std::string::npos), ""
            };
        }
        else
        {
            return std::pair<std::string, std::string> {
                str.substr(1, question_pos - 1),
                str.substr(question_pos, std::string::npos)
            };
        }
    }

  public:
    ControllerManager(ActionManager& am) : _am { am } {}

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

    http::response<http::string_body>
    get_response(http::request<http::string_body>&& req)
    {
        std::string request_str { req.target() };

        auto [command, query_str]
            = _decompose(std::string(request_str));

        auto params = _parse_query_str(query_str);

        auto it = _controllers.find(command);
        if (it == _controllers.end())
        {
            http::response<http::string_body> res { http::status::not_found,
                                                    req.version() };
            res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
            res.set(http::field::content_type, "text/html");
            res.keep_alive(req.keep_alive());
            res.body() = "The controller '" + command + "' was not found.";
            res.prepare_payload();
            return res;
        }
        else
        {
            http::response<http::string_body> res { http::status::ok,
                                                    req.version() };
            res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
            res.set(http::field::content_type, "application/json");
            res.keep_alive(req.keep_alive());
            res.body() = it->second.get()->get_response(params);
            res.prepare_payload();
            return res;
        }
    }
};

#endif
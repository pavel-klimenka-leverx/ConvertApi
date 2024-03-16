#ifndef __CORS_MIDDLEWARE_HPP__
#define __CORS_MIDDLEWARE_HPP__

#include "crow/crow.h"
#include "logger.hpp"
#include <vector>

class CorsMiddleware
{
private:
    Logger logger;
    bool credentials{false};
    std::vector<std::string> allowedOrigins;
    std::vector<std::string> allowedMethods;
    std::vector<std::string> allowedHeaders;
public:
    struct context{};

    void before_handle(crow::request& request, crow::response& response, context& ctx);
    void after_handle(crow::request& request, crow::response& response, context& ctx);

    void allowCredentials() noexcept;
    void allowMethods(std::initializer_list<std::string> methods);
    void allowHeaders(std::initializer_list<std::string> headers);
    void allowOrigins(std::initializer_list<std::string> origins);
    void allowOrigins(const char* const* origins, size_t count);
};

#endif // __CORS_MIDDLEWARE_HPP__
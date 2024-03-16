#include "cors_middleware.hpp"
#include "fmt/format.h"
#include <sstream>

#define ALLOW_METHODS_HEADER "Access-Control-Allow-Methods"
#define ALLOW_HEADERS_HEADER "Access-Control-Allow-Headers"
#define ALLOW_CREDENTIALS_HEADER "Access-Control-Allow-Credentials"
#define ALLOW_ORIGING_HEADER "Access-Control-Allow-Origin"
#define TRUE "true"
#define FALSE "false"

std::string constructCommaSeparatedList(const std::vector<std::string>& list)
{
    if(list.empty()) return "";

    std::stringstream ss;
    for(const std::string& str : list)
        ss << str << ", ";
    std::string result = ss.str();
    return result.substr(0u, result.size() - 2);
}

void CorsMiddleware::before_handle(crow::request& request, crow::response& response, context& ctx)
{}

void CorsMiddleware::after_handle(crow::request& request, crow::response& response, context& ctx)
{
    response.add_header(ALLOW_METHODS_HEADER, constructCommaSeparatedList(allowedMethods));
    response.add_header(ALLOW_CREDENTIALS_HEADER, credentials ? TRUE : FALSE);
    response.add_header(ALLOW_HEADERS_HEADER, constructCommaSeparatedList(allowedHeaders));

    std::string origin = request.get_header_value("Origin");
    if(origin.empty()) return;

    auto allowedOriginIt = std::find(allowedOrigins.begin(), allowedOrigins.end(), origin);
    if(allowedOriginIt == allowedOrigins.end()) return;

    response.add_header(ALLOW_ORIGING_HEADER, origin);
}

void CorsMiddleware::allowCredentials() noexcept
{
    credentials = true;
}

void CorsMiddleware::allowMethods(std::initializer_list<std::string> methods)
{
    allowedMethods.insert(allowedMethods.end(), methods);
}

void CorsMiddleware::allowHeaders(std::initializer_list<std::string> headers)
{
    allowedHeaders.insert(allowedHeaders.end(), headers);
}

void CorsMiddleware::allowOrigins(std::initializer_list<std::string> origins)
{
    allowedOrigins.insert(allowedOrigins.end(), origins);
}

void CorsMiddleware::allowOrigins(const char* const* origins, size_t count)
{
    for(int i = 0; i < count; ++i)
        allowedOrigins.push_back(std::string(origins[i]));
}
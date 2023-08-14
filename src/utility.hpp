#ifndef __UTILITY_HPP__
#define __UTILITY_HPP__

#include <string>

std::string toLower(const std::string& str)
{
    std::string result;
    result.reserve(str.length());
    for(const char& ch : str)
    {
        result.push_back(std::tolower(ch));
    }

    return std::move(result);
}

#endif // __UTILITY_HPP__
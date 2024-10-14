#ifndef HELPERS_H
#define HELPERS_H

#include <string>
#include <sstream>
#include <iomanip>

template <typename T>
std::string convertToString(const T &value, int precision = 2)
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision) << value;
    return ss.str();
}

#endif
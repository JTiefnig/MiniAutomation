#ifndef HELPERS_H
#define HELPERS_H

#include <Arduino.h>
#include <string>
#include <vector>
#include <functional>
#include <sstream>
#include <iterator>
#include <iomanip>

template <typename... X>
class CallbackManager;
template <typename... Ts>
class CallbackManager<void(Ts...)>
{
public:
    /// Add a callback to the list.
    void add(std::function<void(Ts...)> &&callback) { this->callbacks_.push_back(std::move(callback)); }

    /// Call all callbacks in this manager.
    void call(Ts... args)
    {
        for (auto &cb : this->callbacks_)
            cb(args...);
    }
    size_t size() const { return this->callbacks_.size(); }

    void operator()(Ts... args) { call(args...); }

protected:
    std::vector<std::function<void(Ts...)>> callbacks_;
};

template <typename T>
std::string convertToString(const T &value, int precision = 2)
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision) << value;
    return ss.str();
}

#endif
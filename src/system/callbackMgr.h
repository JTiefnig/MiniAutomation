#ifndef CALLBACK_MGR_H
#define CALLBACK_MGR_H

#include <vector>
#include <functional>
#include <iterator>

template <typename... X>
class CallbackManager;
template <typename... Ts>
class CallbackManager<void(Ts...)>
{
public:
    using CallbackType = std::function<void(Ts...)>;

    /// Add a callback to the list.
    void add(CallbackType &&callback) { this->callbacks_.push_back(std::move(callback)); }

    /// Remove a callback from the list.
    void remove(CallbackType &&callback)
    {
        auto it = std::find(this->callbacks_.begin(), this->callbacks_.end(), callback);
        if (it != this->callbacks_.end())
            this->callbacks_.erase(it);
    }

    /// Call all callbacks in this manager.
    void call(Ts... args)
    {
        if (this->isCalling_ && this->recursionSuppression)
            return;
        this->isCalling_ = true;
        for (auto &cb : this->callbacks_)
            cb(args...);
        this->isCalling_ = false;
    }
    size_t size() const { return this->callbacks_.size(); }

    void operator()(Ts... args) { call(args...); }

    bool recursionSuppressionActive() const { return this->isCalling_; }
    bool recursionSuppression = true;

protected:
    bool isCalling_ = false;
    std::vector<CallbackType> callbacks_;
};

#endif // !CALLBACK_MGR_H
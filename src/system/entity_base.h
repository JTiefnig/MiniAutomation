#ifndef ENTITY_H
#define ENTITY_H
#include <string>
#include <functional>
#include "callbackMgr.h"

class EntityBase
{
public:
    using CallbackType = void(const EntityBase &);

private:
    CallbackManager<CallbackType> callbacks;

protected:
    const std::string name;

    void callCallbacks()
    {
        callbacks.call(*this);
    }

public:
    EntityBase(const std::string name);
    ~EntityBase();

    void addCallback(CallbackType callback);
    void removeCallback(CallbackType callback);

    std::string getName() const;
};

#endif

#ifndef ENTITY_H
#define ENTITY_H
#include <string>
#include <functional>
#include "helpers.h"

class EntityBase
{
protected:
    const std::string name;
    CallbackManager<void()> callbacks;

public:
    EntityBase(const std::string name);
    ~EntityBase();

    std::string getName() const;

    virtual void process(const std::string message) = 0;

    void addCallback(std::function<void()> callback);
};

#endif

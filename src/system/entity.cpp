#include "entity.h"

EntityBase::EntityBase(const std::string name)
    : name(name)
{
}

EntityBase::~EntityBase()
{
}

std::string EntityBase::getName() const
{
    return this->name;
}

void EntityBase::addCallback(std::function<void()> callback)
{
    this->callbacks.add(std::move(callback));
}
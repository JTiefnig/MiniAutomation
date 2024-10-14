#include "entity_base.h"
#include <utility>

EntityBase::EntityBase(const std::string name)
    : name(name), callbacks()
{
}

EntityBase::~EntityBase()
{
}

std::string EntityBase::getName() const
{
    return this->name;
}

void EntityBase::addCallback(EntityBase::CallbackType callback)
{
    this->callbacks.add(std::move(callback));
}
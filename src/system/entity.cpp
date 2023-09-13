#include "entity.h"

Entity::Entity(const std::string name)
    : name(name)
{
}

Entity::~Entity()
{
}

std::string Entity::getName() const
{
    return this->name;
}
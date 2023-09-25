#ifndef H_ENTITY_HANDLER
#define H_ENTITY_HANDLER
#include "entity.h"
#include <vector>

class EntityHandler
{
private:
    /* data */
    std::vector<EntityBase *> entities;

public:
    friend class EntityBase;

    void addEntity(EntityBase *entity)
    {
        entities.push_back(entity);
    }

    EntityHandler(/* args */)
    {
    }
    ~EntityHandler()
    {
    }
};

#endif
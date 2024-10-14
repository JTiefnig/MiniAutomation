#ifndef EntityHandler_h
#define EntityHandler_h

#include <map>
#include "entity_base.h"

class EntityHandler
{
private:
    /* data */
    std::map<std::string, EntityBase *> entites;

public:
    EntityHandler(/* args */);
    ~EntityHandler();
};

#endif // !EntityHandler_h
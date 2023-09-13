#ifndef ENTITY_H
#define ENTITY_H
#include <string>

class Entity
{
private:
    const std::string name;
public:
    Entity(const std::string name);
    ~Entity();

    std::string getName() const;

    virtual void process(const std::string message) = 0;
};


#endif

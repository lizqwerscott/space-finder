#ifndef TOOL_H
#define TOOL_H 

#include "../Item.h"

class Person;

class Tool : public Item
{
public:
    Tool(std::string name, double volume, double quality) : 
        Item(name, std::string("Tool"), volume, quality) {}
    virtual ~Tool() {}
public:
    virtual void use(Person * person, PhysicalWorld * world) = 0;
    virtual void rightClick(Person * person, b2Vec2 pos, PhysicalWorld * world) = 0;
public:
    virtual void drawT(Person * person) {}
};

#endif /* TOOL_H */

#ifndef CONSUME_H
#define CONSUME_H

#include "../Item.h"

class Entity;

class Consume : public Item
{
public:
    Consume(std::string name, double volume, double quality) : 
        Item(name, std::string("Consume"), volume, quality)
    {
    }
    ~Consume() {}
};

#endif /* CONSUME_H */

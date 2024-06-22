#ifndef WEAPON_H
#define WEAPON_H

#include "../Item.h"

class Person;

class Weapon : public Item
{
public:
    Weapon(std::string name, double volume, double quality) : 
        Item(name, std::string("Weapon"), volume, quality) {}
    virtual ~Weapon() {}
public:
    virtual void attack(Person * person, PhysicalWorld * world) = 0;
};

#endif /* WEAPON_H */

#ifndef CUBEWIRE_H
#define CUBEWIRE_H

#include "../Entity.h"

class CubeWire : public Entity
{
public:
    CubeWire(std::string name, GameObject * parent, b2Vec2 size, b2Vec2 nodePos, double hp = 10);
    virtual ~CubeWire() {}
public:
    virtual void onFace(Person * person) {}
};

#endif

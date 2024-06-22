#ifndef CUBEENERGYWIRE_H
#define CUBEENERGYWIRE_H

#include "../Entity.h"

class CubeEnergyWire : public Entity
{
public:
    CubeEnergyWire(std::string name, GameObject * parent, b2Vec2 size, b2Vec2 nodePos, double hp = 10);
    virtual ~CubeEnergyWire();
public:
    virtual void onFace(Person * person) {}
};

#endif

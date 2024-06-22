#ifndef CUBEENERGYCWIRE_H
#define CUBEENERGYCWIRE_H

#include "../Entity.h"

class CubeEnergyCWire : public Entity
{
public:
    CubeEnergyCWire(std::string name, GameObject * parent, b2Vec2 size, b2Vec2 nodePos, double hp = 10);
    virtual ~CubeEnergyCWire();
public:
    virtual void onFace(Person * person) {}
};

#endif

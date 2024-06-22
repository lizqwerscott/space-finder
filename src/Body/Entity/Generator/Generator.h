#ifndef GENERATOR_H
#define GENERATOR_H

#include "../Entity.h"

class Generator : public Entity
{
public:
    Generator(std::string name, GameObject * parent, b2Vec2 nodePos, b2Vec2 size, double hp = 100, float generatorSpeed = 10, float energyMax = 1000);
    virtual ~Generator() {}
public:
    virtual void onFace(Person * person) override;
public:
    virtual void UpdateSelf(sf::Time &dt) override;
    virtual void DrawUiSelf() override;
};

#endif

#ifndef NETGENERATOR_H
#define NETGENERATOR_H

#include "../NetEnergy/NetEnergy.h"

class NetGenerator : public NetEnergy
{
public:
    NetGenerator(float generatorSpeed, float energyMax);
    virtual ~NetGenerator();
public:
    virtual void UpdateSelf(sf::Time &dt) override;
    virtual float getEnergy(float needEnergy) override;
public:
    float getSpeed();
private:
    float m_generatorSpeed;
};


#endif

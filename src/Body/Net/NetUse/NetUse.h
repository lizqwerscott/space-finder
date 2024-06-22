#ifndef NETUSE_H
#define NETUSE_H

#include "../NetEnergy/NetEnergy.h"

class NetUse : public NetEnergy
{
public:
    NetUse(float energyMax, float energyUseSpeed = 1);
    virtual ~NetUse();
public:
    virtual void UpdateSelf(sf::Time &dt) override;
    virtual float getEnergy(float needEnergy) override;
private:
    float m_energyUseSpeed;
};

#endif

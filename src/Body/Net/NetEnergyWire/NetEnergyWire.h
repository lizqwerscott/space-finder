#ifndef NETENERGYWIRE_H
#define NETENERGYWIRE_H

#include "../NetEnergy/NetEnergy.h"

class NetEnergyWire : public NetEnergy
{
public:
    NetEnergyWire();
    virtual ~NetEnergyWire();
public:
    virtual float getEnergy(float needEnergy) override;
};

#endif

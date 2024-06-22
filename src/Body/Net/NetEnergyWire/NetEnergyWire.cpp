#include "NetEnergyWire.h"

NetEnergyWire::NetEnergyWire() : NetEnergy("NetEnergyWire", 0)
{
    
}

NetEnergyWire::~NetEnergyWire()
{
    
}

float NetEnergyWire::getEnergy(float needEnergy)
{
    std::vector<NetEnergy *> searchs;
    return this->runNode(searchs, needEnergy);
}


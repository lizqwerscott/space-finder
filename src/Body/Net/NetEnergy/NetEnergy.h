#ifndef NETENERGY_H
#define NETENERGY_H

#include "../Net.h"

class NetEnergy : public Net
{
public:
    NetEnergy(std::string typeName, float energyMax);
    virtual ~NetEnergy();
// public:
//     virtual void UpdateSelf(sf::Time &dt) override;
public:
    virtual float getEnergy(float needEnergy);
    float runNode(std::vector<NetEnergy *> searchs, float needEnergy);
public:
    float getSaveEnergy();
    float getMax();
    void increaseEnergy(float step);
    void decreaseEnergy(float step);
public:
    std::string m_energyTypeName;
    float m_energyMax;
    float m_energy;
};

#endif

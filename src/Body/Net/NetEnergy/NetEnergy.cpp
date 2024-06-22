#include "NetEnergy.h"
#include <algorithm>

#include "../NetGenerator/NetGenerator.h"

NetEnergy::NetEnergy(std::string typeName, float enerygMax) :
    Net("Energy"),
    m_energyTypeName(typeName),
    m_energyMax(enerygMax),
    m_energy(0)
{
    
}

NetEnergy::~NetEnergy()
{
    
}

float NetEnergy::getEnergy(float needEnergy)
{
    std::vector<NetEnergy *> searchs;
    return this->runNode(searchs, needEnergy);
}

float NetEnergy::runNode(std::vector<NetEnergy *> searchs, float needEnergy)
{
    for (auto net : this->m_connectNets) {
	if (net->m_typename == "Energy") {
	    auto energy = static_cast<NetEnergy *>(net);
	    auto it = find(searchs.begin(), searchs.end(), energy);
	    if (it != searchs.end()) {
		return 0;
	    } else {
		searchs.push_back(this);
		if (energy->m_energyTypeName == "NetGenerator") {
		    auto generator = static_cast<NetGenerator *>(energy);
		    return generator->getEnergy(needEnergy);
		}
		return energy->runNode(searchs, needEnergy);
	    }
	}
    }
    return 0;
}

float NetEnergy::getSaveEnergy()
{
    return this->m_energy;
}

float NetEnergy::getMax()
{
    return this->m_energyMax;
}

void NetEnergy::increaseEnergy(float step)
{
    if (this->m_energy + step <= this->m_energyMax) {
	this->m_energy += step;
    }
}

void NetEnergy::decreaseEnergy(float step)
{
    if (this->m_energy - step >= 0) {
	this->m_energy -= step;
    }
}


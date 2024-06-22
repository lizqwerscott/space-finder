#include "NetUse.h"

NetUse::NetUse(float energyMax, float energyUseSpeed) :
    NetEnergy("NetUse", energyMax),
    m_energyUseSpeed(energyUseSpeed)
{

}

NetUse::~NetUse()
{

}

void NetUse::UpdateSelf(sf::Time &dt)
{
    // use energy
    if (this->m_energy >= 0) {
	float step = dt.asSeconds() / 1 * this->m_energyUseSpeed;
	this->decreaseEnergy(step);
    }
    // get energy
    if (this->m_energy <= this->m_energyMax) {
	// 最低需要能量
	// float step = this->getEnergy(dt.asSeconds() * this->m_energyUseSpeed);
	// if (this->m_energy + step <= this->m_energyMax) {
	//     this->m_energy += step;
	// }
	// 最大能量需求
	float step = this->getEnergy(this->m_energyMax - this->m_energy);
	this->increaseEnergy(step);
    }
    // Log::printLog("Use:Energy: %f\n", this->m_energy);
}

float NetUse::getEnergy(float needEnergy)
{
    std::vector<NetEnergy *> searchs;
    return this->runNode(searchs, needEnergy);
}

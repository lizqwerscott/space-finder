#include "NetGenerator.h"

NetGenerator::NetGenerator(float generatorSpeed, float energyMax) :
    NetEnergy("NetGenerator", energyMax),
    m_generatorSpeed(generatorSpeed)
{
    
}

NetGenerator::~NetGenerator()
{
    
}

void NetGenerator::UpdateSelf(sf::Time &dt)
{
    if (this->m_energy <= this->m_energyMax) {
	Log::setLevel(LOG_LEVEL_INFO);
	double step = dt.asSeconds() / 1 * m_generatorSpeed;
	this->increaseEnergy(step);
	// Log::printLog("dt: %lf\n", dt.asSeconds());
	// Log::printLog("step: %lf, energy: %f\n", step, m_generatorEnergy);
    }
}

float NetGenerator::getEnergy(float needEnergy)
{
    if (needEnergy <= this->m_energy) {
	this->m_energy -= needEnergy;
	return needEnergy;
    } else {
	return 0;
    }
}

float NetGenerator::getSpeed()
{
    return this->m_generatorSpeed;
}


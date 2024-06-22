#include "CubeEnergyWire.h"
#include "../../Net/NetEnergyWire/NetEnergyWire.h"

CubeEnergyWire::CubeEnergyWire(std::string name, GameObject * parent, b2Vec2 size, b2Vec2 nodePos, double hp) :
    Entity(name, "CubeEnergyWire", parent, nodePos, hp)
{
    this->m_netEnergy = new NetEnergyWire();
    this->m_isDrawUi = false;

    sf::Texture * tieWireTexture = ResourceManager::GetTexture(std::string("energyTie"));
    tieWireTexture->setSmooth(true);

    m_mainShape = CreateRectangleShape(size, tieWireTexture);
}

CubeEnergyWire::~CubeEnergyWire()
{
    
}


#include "CubeEnergyCWire.h"
#include "../../Net/NetEnergyWire/NetEnergyWire.h"
#include "../../Net/NetWire/NetWire.h"

CubeEnergyCWire::CubeEnergyCWire(std::string name, GameObject * parent, b2Vec2 size, b2Vec2 nodePos, double hp) :
    Entity(name, "CubeEnergyCWire", parent, nodePos, hp)
{
    this->m_netEnergy = new NetEnergyWire();
    this->m_netControl = new NetWire();
    this->m_isDrawUi = false;

    sf::Texture * tieEnergyCWireTexture = ResourceManager::GetTexture(std::string("energyCWire"));
    tieEnergyCWireTexture->setSmooth(true);

    m_mainShape = CreateRectangleShape(size, tieEnergyCWireTexture);
}

CubeEnergyCWire::~CubeEnergyCWire()
{
    
}


#include "CubeWire.h"
#include "../../Net/NetWire/NetWire.h"

CubeWire::CubeWire(std::string name, GameObject * parent, b2Vec2 size, b2Vec2 nodePos, double hp) :
    Entity(name, "CubeWire", parent, nodePos, hp)
{
    this->m_netControl = new NetWire();
    this->m_isDrawUi = false;

    sf::Texture * tieWireTexture = ResourceManager::GetTexture(std::string("wireTie"));
    tieWireTexture->setSmooth(true);

    m_mainShape = CreateRectangleShape(size, tieWireTexture);
}

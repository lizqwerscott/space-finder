#include "Cube.h"

Cube::Cube(std::string name, GameObject * parent, b2Vec2 size, b2Vec2 nodePos, double hp) :
    Entity(name, "Cube", parent, nodePos, hp)
{
    this->m_isDrawUi = false;

    sf::Texture * tieTexture = ResourceManager::GetTexture(std::string("tie"));
    tieTexture->setSmooth(true);

    m_mainShape = CreateRectangleShape(size, tieTexture);
}

void Cube::onContact(Entity *entity)
{
}

void Cube::onEndContact(Entity *entity)
{
}

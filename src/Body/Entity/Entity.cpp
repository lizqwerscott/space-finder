#include "Entity.h"
#include "slt/utils.h"
#include <cstdint>

Entity::Entity(std::string name, const std::string &typeName, GameObject * parent, b2Vec2 nodePos, double hp) :
    GameObject(name, parent, hp),
    m_typeName(typeName)
{
    this->SetPosition(nodePos);
}

Entity::~Entity()
{
    if (this->m_netControl != nullptr) {
	delete this->m_netControl;
	this->m_netControl = nullptr;
    }

    if (this->m_netEnergy != nullptr) {
	delete this->m_netEnergy;
	this->m_netEnergy = nullptr;
    }
}

void Entity::initPhysical(b2BodyDef bodyDef, b2FixtureDef fixtureDef, PhysicalWorld * world, const std::string &bodyName, const std::string &fixtureName)
{
    auto physicalBody = CreatePhysicalBody(bodyName, b2Vec2(0, 0), bodyDef, world);
    auto fixture = physicalBody->CreateFixture(fixtureName, fixtureDef);
    user_data_set(physicalBody->GetBody()->GetUserData().pointer, 1, reinterpret_cast<uintptr_t>(this));
    user_data_set(fixture->m_fixture->GetUserData().pointer, 1, reinterpret_cast<uintptr_t>(this));
}

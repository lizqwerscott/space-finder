#ifndef ENTITY_H
#define ENTITY_H

#include "../GameObject.h"
#include "../Net/Net.h"
#include "../Net/NetControl/NetControl.h"
#include "../Net/NetEnergy/NetEnergy.h"

using namespace slt;

class Person;

class Entity : public GameObject
{
public:
    Entity(std::string name, const std::string &typeName, GameObject * parent, b2Vec2 nodePos = b2Vec2(0, 0), double hp = 1);
    virtual ~Entity();
public:
    void initPhysical(b2BodyDef bodyDef, b2FixtureDef fixtureDef, PhysicalWorld * world, const std::string &bodyName = "MainBody", const std::string &fixtureName = "MainFixture");
public:
    virtual void onFace(Person * person) {}
    virtual void onContact(Entity * entity) {}
    virtual void onEndContact(Entity * entity) {}
public:
    bool m_isControl = false;
    bool m_isConnect = false;
    std::string m_typeName;

    NetEnergy * m_netEnergy = nullptr;
    NetControl * m_netControl = nullptr;
};

#endif /* ENTITY_H */

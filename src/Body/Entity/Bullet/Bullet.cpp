#include "Bullet.h"

Bullet::Bullet(std::string name, GameObject * parent, PhysicalWorld * world, b2Vec2 nodePos) :
    Entity(name, "Bullet", parent, nodePos, 1)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2BodyType::b2_dynamicBody;
    bodyDef.position =
        Math::WorldCoordSToPhysicalCoordS(this->GetPosition());
    bodyDef.angle = 0;
    bodyDef.bullet = true;

    b2CircleShape circleShape;
    circleShape.m_p = b2Vec2(0, 0);
    circleShape.m_radius = 0.2; // radius
    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.1;
    fixtureDef.friction = 0.3;
    fixtureDef.shape = &circleShape;
    fixtureDef.restitution = 1;
    initPhysical(bodyDef, fixtureDef, world, "BulletBody", "BulletFixture");

    sf::Texture * bulletTexture = ResourceManager::GetTexture(std::string("bullet1"));
    bulletTexture->setSmooth(true);

    m_mainShape = CreateRectangleShape(b2Vec2(0.2, 0.2), bulletTexture);
}

void Bullet::onContact(Entity *entity)
{
    

}

void Bullet::onEndContact(Entity *entity)
{
    this->setHp(0);
    Log::printLog("Remove bullet: %d\n", GetId());
    GetParent()->DeleteChild(GetId());
}

void Bullet::setInitSpeed(b2Vec2 speed)
{
    this->GetPhysicalBody()->GetBody()->ApplyLinearImpulseToCenter(speed, true);
}

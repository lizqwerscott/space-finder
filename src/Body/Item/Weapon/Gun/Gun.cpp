#include "Gun.h"
#include "../../../Entity/Bullet/Bullet.h"
#include "../../../Entity/Biological/Person.h"
#include "../../Consume/BulletI/BulletI.h"
#include "../../../Entity/EntityFactory.h"

#include <cstdio>

Gun::Gun(std::string name, double volume, double quality, int maxBulletN) :
    Weapon(name, volume, quality),
    m_nowBulletN(0),
    m_maxBulletN(maxBulletN),
    m_bulletN(-1000)
{
}

Gun::~Gun()
{
}

void Gun::attack(Person *person, PhysicalWorld * world)
{
    b2Vec2 targetPos = Math::NumberProduct(person->getFace(), 1.3);
    fire(person, world, targetPos);
}

void Gun::fire(Person * person, PhysicalWorld * world, b2Vec2 position)
{
    if (m_nowBulletN == 0) {
        Log::setLevel(LOG_LEVEL_WARNING);
        Log::printLog("need load bullet\n");
        return;
    }
    auto bullet = static_cast<Bullet *>(EntityFactory::generateEntity("bullet", position + person->GetPosition()));
    bullet->setInitSpeed(b2Vec2(position.x * 30, position.y * 30));

    Log::setLevel(LOG_LEVEL_INFO);
    Log::printLog("Create bullet:%u, pos:%f,%f\n", bullet->GetId(), position.x, position.y);
    m_bulletN++;
    m_nowBulletN--;
}

void Gun::loadBullet(BulletI *bullet)
{
    if (m_nowBulletN == m_maxBulletN) {
        return;
    }
    delete bullet;
    m_nowBulletN++;
    Log::setLevel(LOG_LEVEL_INFO);
    Log::printLog("[LoadBullet]: %d\n", m_nowBulletN);
}



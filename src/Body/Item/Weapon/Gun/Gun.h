#ifndef GUN_H
#define GUN_H

#include "../Weapon.h"

class BulletI;
class GameObject;

class Gun : public Weapon
{
public:
    Gun(std::string name, double volume, double quality, int maxBulletN);
    ~Gun();
public:
    virtual void attack(Person * person, PhysicalWorld * world);
public:
    void fire(Person * person, PhysicalWorld * world, b2Vec2 position);
    void loadBullet(BulletI * bullet);
    bool isLoadFull() {return m_nowBulletN == m_maxBulletN;}
public:
    int getBulletN() {return m_nowBulletN;}
    int getMaxBulletN() {return m_maxBulletN;}
private:
    int m_nowBulletN;
    int m_maxBulletN;
    int m_bulletN;
};

#endif /* GUN_H */

#ifndef GYRO_H
#define GYRO_H

#include "../Entity.h"

class Gyro : public Entity
{
public:
    Gyro(std::string name, GameObject * parent, b2Vec2 size, b2Vec2 nodePos = b2Vec2(0, 0), double hp = 90);
    virtual ~Gyro();
public:
    virtual void UpdateSelf(sf::Time &dt) override;
private:
    void rotate(float angle);
public:
    bool start;
};

#endif

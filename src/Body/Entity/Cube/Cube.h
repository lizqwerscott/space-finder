#ifndef CUBE_H
#define CUBE_H

#include "../Entity.h"

class Cube : public Entity
{
public:
    Cube(std::string name, GameObject * parent, b2Vec2 nodePos, b2Vec2 size, double hp = 100);
    virtual ~Cube() {}
public:
    virtual void onFace(Person * person) {}
    void onContact(Entity *entity) override;
    void onEndContact(Entity *entity) override;
};

#endif /* CUBE_H */

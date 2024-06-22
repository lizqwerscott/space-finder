#ifndef BOX_H
#define BOX_H

#include "../Entity.h"
#include "../../BoxBase.h"

using namespace slt;

class Item;

class Box : public Entity, public BoxBase
{
public:
    Box(std::string name, GameObject * parent, double volume, double quality, b2Vec2 nodePos = b2Vec2(0, 0), double hp = 1);
    ~Box();
public:
    virtual void onFace(Person * person) override;
    virtual void DrawUiSelf() override;
};

#endif /* BOX_H */

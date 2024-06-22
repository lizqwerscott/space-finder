#ifndef ARCWELDING_H
#define ARCWELDING_H

#include "../Tool.h"

class ArcWelding : public Tool
{
public:
    ArcWelding(std::string name, double volume, double quality);
    virtual ~ArcWelding() {}
public:
    void connectEntity(Entity * e1, Entity * e2, PhysicalWorld * world);
public:
    virtual void use(Person * person, PhysicalWorld * world) override;
    virtual void rightClick(Person * person, b2Vec2 pos, PhysicalWorld * world) override;
public:
    virtual void drawT(Person * person) override;
public:
    std::string m_generateEntity;
    bool m_isAutoConnect = true;
};

#endif /* ARCWELDING_H */

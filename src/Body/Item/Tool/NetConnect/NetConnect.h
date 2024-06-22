#ifndef NETCONNECT_H
#define NETCONNECT_H

#include "../Tool.h"

class NetConnect : public Tool 
{
public:
    NetConnect(std::string name, double volume, double quality);
    virtual ~NetConnect();
public:
    virtual void use(Person * person, PhysicalWorld * world);
    virtual void rightClick(Person * person, b2Vec2 pos, PhysicalWorld * world) {}
public:
    Entity * m_firstEntity = nullptr;
};

#endif /* NETCONNECT_H */

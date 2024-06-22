#ifndef CUTTINGMACHINE_H
#define CUTTINGMACHINE_H

#include "../Tool.h"

class CuttingMachine : public Tool
{
public:
    CuttingMachine(std::string name, double volume, double quality);
    virtual ~CuttingMachine() {}
public:
    virtual void use(Person * person, PhysicalWorld * world);
    virtual void rightClick(Person * person, b2Vec2 pos, PhysicalWorld * world);
};

#endif /* CUTTINGMACHINE_H */

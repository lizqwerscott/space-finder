#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <slt/AllSub.h>
#include <iostream>

using namespace slt;

class GameObject : public SNode
{
public:
    GameObject(std::string name, GameObject * parent, double hp = 1);
    virtual ~GameObject();
public:
    double getHp() {return this->m_hp;}
    void increaseHp(double setp) {m_hp = m_hp + setp;}
    void decreaseHp(double setp) {m_hp = m_hp - setp;}
    void setHp(double hp) {m_hp = hp;}
private:
    double m_hp = 0;
};

#endif /* GAMEOBJECT_H */

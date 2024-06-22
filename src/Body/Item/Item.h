#ifndef ITEM_H
#define ITEM_H

#include <slt/AllSub.h>

using namespace slt;

class Entity;

class Item
{
public:
    Item(std::string name, std::string typeName, double volume, double quality) :
        m_volume(volume),
        m_quality(quality),
        m_name(name),
        m_typeName(typeName),
        m_equipEntity(nullptr)
    {}
    virtual ~Item() {}
public:
    void setEquip(Entity * equipEntity) {m_equipEntity = equipEntity;}
    bool isEquip() {return m_equipEntity != nullptr;}
public:
    virtual void update() {}
    virtual void draw() {}
public:
    double getVolume() {return m_volume;}
    double getQuality() {return m_quality;}
    std::string getName() {return m_name;}
    std::string getTypeName() {return m_typeName;}
private:
    double m_volume;
    double m_quality;
    std::string m_name;
    std::string m_typeName;
protected:
    Entity * m_equipEntity;
};

#endif /* ITEM_H */

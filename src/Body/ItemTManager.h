#ifndef ITEMTMANAGER_H
#define ITEMTMANAGER_H

#include "slt/AllSub.h"

using namespace slt;

class ContainerBase;

class ItemTManager
{
public:
public:
    static void Create();
    static void Destory();
public:
    static void drag(ContainerBase * box, std::string name);
    static void disDrag();
    static bool isDrag();
    static void hoveredBox(ContainerBase * box);
    static void disHoveredBox(ContainerBase * box);
private:
    // when mouse drag item, they put it in this;
    ContainerBase * m_box = nullptr;
    std::string m_dragName;
    bool m_isDrag = false;
    //when mouse hovered box, they put it in this;
    ContainerBase * m_lastHoveredBox = nullptr;
private:
    ItemTManager() {}
    virtual ~ItemTManager() {}
};

#endif /* ITEMTMANAGER_H */

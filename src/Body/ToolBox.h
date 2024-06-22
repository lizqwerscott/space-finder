#ifndef TOOLBOX_H
#define TOOLBOX_H

#include "ContainerBase.h"

class ToolBox : public ContainerBase
{
public:
    ToolBox(double volume, double quality);
    virtual ~ToolBox();
public:
    virtual void DrawBoxUi(std::string name, int row = 1, int column = 3);
public:
    virtual bool addItem(Item * item);
    virtual Item * getItem(std::string name = "");
    virtual bool transferItem(ContainerBase * target, std::string name = "", int number = 1);
public:
    virtual bool isEmpty();
protected:
    Item * m_container = nullptr;
};

#endif /* TOOLBOX_H */


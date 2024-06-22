#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include "Item.h"

class ItemFactory
{
public:
    static void addItem(std::string name, std::function<Item * ()> map);
    static void removeEntity(std::string name);
    //static Item * generateItem(std::string name);
    static Item * generateItem(const std::string &name);
public:
    static std::vector<std::string> getAll();
public:
    static void Create();
    static void Destroy();
private:
    std::map<std::string, std::function<Item * ()>> m_itemMap;
private:
    ItemFactory();
    virtual ~ItemFactory();

};

#endif /* ITEMFACTORY_H */

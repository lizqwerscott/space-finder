#include "ItemFactory.h"

ItemFactory * itemFactory = nullptr;

ItemFactory::ItemFactory()
{
}

ItemFactory::~ItemFactory()
{
}

void ItemFactory::Create()
{
    if (itemFactory == nullptr) {
        itemFactory = new ItemFactory();
    }
}

void ItemFactory::Destroy()
{
    if (itemFactory != nullptr) {
        delete itemFactory;
        itemFactory = nullptr;
    }
}

void ItemFactory::addItem(std::string name, std::function<Item *()> map)
{
    itemFactory->m_itemMap[name] = map;
}

void ItemFactory::removeEntity(std::string name)
{
    auto iter = itemFactory->m_itemMap.find(name);
    if (iter != itemFactory->m_itemMap.end()) {
        itemFactory->m_itemMap.erase(iter);
    }
}

/*
Item * ItemFactory::generateItem(std::string name)
{
    auto iter = itemFactory->m_itemMap.find(name);
    Item * item = nullptr;
    if (iter != itemFactory->m_itemMap.end()) {
        item = iter->second();
    } else {
        Log::setLevel(LOG_LEVEL_ERROR);
        Log::printLog("[ItemFactory]:can't find it:%s\n", name.c_str());
    }
    return item;
}
*/

Item * ItemFactory::generateItem(const std::string &name)
{
    auto iter = itemFactory->m_itemMap.find(name);
    Item * item = nullptr;
    if (iter != itemFactory->m_itemMap.end()) {
        item = iter->second();
    } else {
        Log::setLevel(LOG_LEVEL_ERROR);
        Log::printLog("[ItemFactory]:can't find it:%s\n", name.c_str());
    }
    return item;
}

std::vector<std::string>
ItemFactory::getAll()
{
    std::vector<std::string> result;
    for (auto iter : itemFactory->m_itemMap) {
        result.push_back(iter.first);
    }
    return result;
}


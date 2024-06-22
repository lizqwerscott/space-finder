#include "EntityFactory.h"

EntityFactory * entityFactory = nullptr;

EntityFactory::EntityFactory()
{
}

EntityFactory::~EntityFactory()
{
    for (auto data : m_entityMap) {
        delete data.second;
        data.second = nullptr;
    }
    m_entityMap.clear();
}

void EntityFactory::Create()
{
    if (entityFactory == nullptr) {
        entityFactory = new EntityFactory();
    }
}

void EntityFactory::Destroy()
{
    if (entityFactory != nullptr) {
        delete entityFactory;
        entityFactory = nullptr;
    }
}

void EntityFactory::addEntity(entityData * entityData)
{
    entityFactory->m_entityMap[entityData->name] = entityData;
}

entityData * EntityFactory::getEntityData(std::string name)
{
    auto iter = entityFactory->m_entityMap.find(name);
    if (iter != entityFactory->m_entityMap.end()) {
        return iter->second;
    } else {
        return nullptr;
    }
}

void EntityFactory::removeEntity(std::string name)
{
    auto iter = entityFactory->m_entityMap.find(name);
    if (iter != entityFactory->m_entityMap.end()) {
        entityFactory->m_entityMap.erase(iter);
    }
}

Entity * EntityFactory::generateEntity(std::string name, b2Vec2 pos, Entity * mainEntity)
{
    auto iter = entityFactory->m_entityMap.find(name);
    Entity * entity = nullptr;
    if (iter != entityFactory->m_entityMap.end()) {
        entity = iter->second->init(pos, mainEntity);
        entity->init();
    } else {
        Log::setLevel(LOG_LEVEL_ERROR);
        Log::printLog("[EntityFactory]:cant 't find it:%s\n", name.c_str());
    }
    return entity;
}

std::vector<std::string>
EntityFactory::getAll()
{
    std::vector<std::string> result;
    for (auto iter : entityFactory->m_entityMap) {
        result.push_back(iter.first);
    }
    return result;
}

#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "Entity.h"

#define factoryFun std::function<Entity * (b2Vec2 pos, Entity * mainEntity)>

struct entityData {
    entityData(const std::string &_name, b2Vec2 _size) :
        name(_name), size(_size)
    {

    }
    b2Vec2 getSize(float _angle = -9898)
    {
	auto wucha = [](float angle1, float angle2, float wuc = 0.1) -> bool {
	    return abs(angle1 - angle2) <= 0.1;
	};

	b2Vec2 _size = this->size;
	if (_angle == -9898) {
	    if (angle == 90 || angle == 270) {
		_size = b2Vec2(size.y, size.x);
	    }
	} else {
	    if (wucha(_angle, PI / 2) || wucha(_angle, PI * 3 / 2)) {
		_size = b2Vec2(size.y, size.x);
	    }
	}
	return _size;
    }
    void increaseAngle()
	{
	    if (this->angle == 270) {
		this->angle = 0;
	    } else {
		this->angle += 90;
	    }
	}
    float getAngle()
	{
	    return Math::degreeToRad(this->angle);
	}
    std::string name;
    b2Vec2 size;
    int angle = 0;
    factoryFun init;
};

class EntityFactory
{
public:
    static void addEntity(entityData * entityData);
    static entityData * getEntityData(std::string name);
    static void removeEntity(std::string name);
    static Entity * generateEntity(std::string name, b2Vec2 pos, Entity * mainEntity = nullptr);
public:
    static std::vector<std::string> getAll();
public:
    static void Create();
    static void Destroy();
private:
    std::map<std::string , entityData *> m_entityMap;
private:
    EntityFactory();
    virtual ~EntityFactory();
};

#endif /* ENTITYFACTORY_H */

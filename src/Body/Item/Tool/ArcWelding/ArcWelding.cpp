#include "ArcWelding.h"
#include "../../../Entity/Biological/Person.h"
#include "../../../Entity/EntityFactory.h"
#include "../../../Net/Net.h"

ArcWelding::ArcWelding(std::string name, double volume, double quality) :
    Tool(name, volume, quality)
{
    Graphic::insertKeyCallBack(sf::Keyboard::G, 0, [this]() -> void {
        m_isAutoConnect = !m_isAutoConnect;
        Log::setLevel(LOG_LEVEL_INFO);
        if (m_isAutoConnect)
        {
            Log::printLog("auto connect is open\n");

        } else
        {
            Log::printLog("auto connect is close\n");
        }
    });
}

void ArcWelding::connectEntity(Entity * e1, Entity * e2, PhysicalWorld * world)
{
    if (e1 != nullptr && e2 != nullptr) {
        Log::printLog("contacts:--------\n");
        b2Vec2 contactCenterPos = e2->GetPosition();
        Log::printLog("finally min: %s, %f, %f\n", e2->GetName().c_str(), contactCenterPos.x, contactCenterPos.y);
        //Contact
        b2WeldJointDef joinDef;
        joinDef.Initialize(e1->m_physicalBody->GetBody(), e2->m_physicalBody->GetBody(), b2Vec2(0, 0));
        world->CreateJoint(&joinDef);
	if (e1->m_netEnergy != nullptr && e2->m_netEnergy != nullptr) {
	    Log::printLog("Connect Energy net\n");
	    Net::connectAnother(e1->m_netEnergy, e2->m_netEnergy);
	}
	if (e1->m_netControl != nullptr && e2->m_netControl != nullptr) {
	    Log::printLog("Connect Control net\n");
	    Net::connectAnother(e1->m_netControl, e2->m_netControl);
	}

    }
}

void ArcWelding::use(Person *person, PhysicalWorld *world)
{
    Log::setLevel(LOG_LEVEL_INFO);
    if (person->isHaveSelected()) {
        b2Vec2 pos = person->getMousePos();
        Entity * faceEntity = person->getFaceEntity();
        auto entity = EntityFactory::generateEntity(m_generateEntity, pos, faceEntity);
        Log::printLog("Together generate: %s, %u, pos: %f, %f \n", m_generateEntity.c_str(), entity->GetId(), pos.x, pos.y);
        if (m_isAutoConnect) {
            //Connect entity and faceEntity
            connectEntity(faceEntity, entity, world);
        }

    } else {
        b2Vec2 pos = person->getMousePos();
        auto entity = EntityFactory::generateEntity(m_generateEntity, pos);
        Log::printLog("Alone generate: %s, %u, pos: %f, %f \n", m_generateEntity.c_str(), entity->GetId(), pos.x, pos.y);
    }
}

void ArcWelding::rightClick(Person * person, b2Vec2 pos, PhysicalWorld * world)
{
    Entity * entity = person->getFaceEntity();
    b2Fixture * fixture = person->getFaceFixture();

    if (entity != nullptr && fixture != nullptr) {
        std::vector<b2Fixture *> m_contants = world->getContact(fixture);
        //Find the nearest body
        Entity * contantEntity = nullptr;
        b2Vec2 faceCenterPos = entity->GetPosition();
        float minLength = 10000; Log::setLevel(LOG_LEVEL_INFO);
        Log::printLog("facePos: %f, %f\n", faceCenterPos.x, faceCenterPos.y);
        Log::printLog("contacts:---------\n");
        for (auto item : m_contants) {
            uintptr_t userData = user_data_convert(item->GetUserData().pointer, 1);
            if (userData != 0) {
                Entity * entityContant = reinterpret_cast<Entity * >(userData);
                if (entityContant != person) {
                    b2Vec2 contactCenterPos = entityContant->GetPosition();
                    Log::printLog("contan:%s, %f, %f\n", entityContant->GetName().c_str(), contactCenterPos.x, contactCenterPos.y);
                    float length = (pos - contactCenterPos).Length();
                    if (length < minLength) {
                        contantEntity = entityContant;
                        minLength = length;
                    }
                }
            }
        }
        Log::printLog("contacts:---------\n");
        Log::printLog("click pos: %f, %f\n", pos.x, pos.y);
        if (contantEntity != nullptr) {
            connectEntity(entity, contantEntity, world);
        }
    }
}

void ArcWelding::drawT(Person * person)
{
    auto data = EntityFactory::getEntityData(m_generateEntity);
    auto faceEntity = person->getFaceEntity();
    if (faceEntity != nullptr) {
	auto faceEntityData = EntityFactory::getEntityData(faceEntity->GetName());
	auto faceEntitySize = faceEntityData->getSize();
        auto nodePos = PhysicalWorld::generateNodePos(faceEntity->m_physicalBody, faceEntitySize, data->getSize());
        // Log::setLevel(LOG_LEVEL_INFO);
        // Log::printLog("faceEntityName: %s\n", faceEntity->GetName().c_str());
        // Log::printLog("faceEntityTypeName: %s\n", faceEntity->m_typeName.c_str());
        // b2AABB aabb;
        b2Vec2 size = data->getSize();

        // aabb.upperBound = b2Vec2(-size.x, size.y) + nodePos;
        // aabb.lowerBound = b2Vec2(size.x, -size.y) + nodePos;
        //Graphic::getInstance()->DrawAABB(&aabb, b2Color(127, 255, 0));

        {
	    // Draw generate entity.
            b2Vec2 vertices[4];
            float angle = faceEntity->GetAngle();
	    // Log::printLog("face angle: %f\n", angle);
	    // auto a = faceEntityData->getSize();
	    // auto b = faceEntityData->getSize(faceEntity->GetAngle());
	    // Log::printLog("last:: %f, %f, then:: %f, %f\n", a.x, a.y, b.x, b.y);

            b2Mat22 mat(cos(angle), sin(angle), -sin(angle), cos(angle));

            b2Vec2 upLeft = mat.Solve(b2Vec2(-size.x, size.y));
            b2Vec2 upRight = mat.Solve(b2Vec2(size.x, size.y));
            b2Vec2 downLeft = mat.Solve(b2Vec2(-size.x, -size.y));
            b2Vec2 downRight = mat.Solve(b2Vec2(size.x, -size.y));

	    vertices[0] = upLeft + nodePos;
	    vertices[1] = upRight + nodePos;
	    vertices[2] = downRight + nodePos;
	    vertices[3] = downLeft + nodePos;

	    Graphic::getInstance()->DrawPolygon(vertices, 4, b2Color(255, 62, 150));

        }

        // Log::printLog("faceEntityAngle: %f\n", faceEntity->GetAngle());

	float angle = faceEntity->GetAngle();
        b2Mat22 mat(cos(angle), sin(angle), -sin(angle), cos(angle));
        b2Vec2 vertices[2];
        b2Vec2 up = mat.Solve(b2Vec2(0, 1));
        vertices[0] = nodePos;
        vertices[1] = up + nodePos;
        // Graphic::getInstance()->DrawPolygon(vertices, 2, b2Color(127, 255, 0));
        Graphic::getInstance()->DrawPolygon(vertices, 2, b2Color(255, 62, 150));
    }
}

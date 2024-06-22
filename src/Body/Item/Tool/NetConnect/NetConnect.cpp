#include "NetConnect.h"
#include "../../../Entity/Biological/Person.h"
#include "../../../Entity/Computer/Computer.h"

NetConnect::NetConnect(std::string name, double volume, double quality) :
    Tool(name, volume, quality)
{
}

NetConnect::~NetConnect()
{
}

void NetConnect::use(Person *person, PhysicalWorld *world)
{
    auto faceEntity = person->getFaceEntity();
    if (m_firstEntity == nullptr) {
        if (faceEntity != nullptr) {
            if (faceEntity->m_isControl) {
                m_firstEntity = faceEntity;
                Log::setLevel(LOG_LEVEL_INFO);
                Log::printLog("add computer\n");
            }
        }
    } else {
        if (faceEntity != nullptr) {
            if (faceEntity != m_firstEntity) {
                Log::setLevel(LOG_LEVEL_INFO);
                Log::printLog("[]%s, add control\n", faceEntity->GetName().c_str());
                Computer * computer = static_cast<Computer *>(m_firstEntity);
                computer->addControl(faceEntity);
                m_firstEntity = nullptr;
            }
        }
    }
}

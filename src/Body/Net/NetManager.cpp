#include "NetManager.h"

NetManager * netManager = nullptr;

NetManager * NetManager::GetInstance()
{
    if (netManager == nullptr) {
	netManager = new NetManager();
    }
    return netManager;
}

void NetManager::Destory()
{
    if (netManager != nullptr) {
	delete netManager;
	netManager = nullptr;
    }
}

NetManager::NetManager()
{
}

NetManager::~NetManager()
{
}


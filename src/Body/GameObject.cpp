#include "GameObject.h"

GameObject::GameObject(std::string name, GameObject * parent, double hp) :
    SNode(name, parent)
{
    parent->AddChild(this);
    if (hp <= 0) {
        Log::setLevel(LOG_LEVEL_ERROR);
        Log::printLog("[ERROR][%s]:this hp must be greater than 0\n", this->GetName().c_str());
    } else {
        m_hp = hp;
    }

    this->pushUpdateCallBack([](SNode * node) -> void {
        auto gameObject = static_cast<GameObject *>(node);
        if (gameObject->m_hp <= 0)
        {
        Log::setLevel(LOG_LEVEL_INFO);
        Log::printLog("[Dead]:%s (%u)hp is zero", gameObject->GetName().c_str(), gameObject->GetId());
            gameObject->GetParent()->DeleteChild(gameObject->GetId());
        }
    });
}

GameObject::~GameObject()
{
    Log::setLevel(LOG_LEVEL_INFO);
    Log::printLog("[Dead]:%s is dead\n", GetName().c_str());
}

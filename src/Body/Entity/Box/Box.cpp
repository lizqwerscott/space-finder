#include "Box.h"
#include "../../Item/Item.h"

Box::Box(std::string name, GameObject *parent, double volume, double quality, b2Vec2 nodePos, double hp) :
    Entity(name, "Box", parent, nodePos, hp),
    BoxBase(volume, quality)
{
    this->m_isDrawUi = false;

    sf::Texture * boxTexture = ResourceManager::GetTexture(std::string("boxtie"));
    boxTexture->setSmooth(true);

    m_mainShape = CreateRectangleShape(b2Vec2(2, 2), boxTexture);
}

Box::~Box() {}

void Box::onFace(Person *person)
{
    Log::setLevel(LOG_LEVEL_INFO);
    Log::printLog("[Box]report box\n");
    this->m_isDrawUi = !this->m_isDrawUi;
}

void Box::DrawUiSelf()
{
    if (this->m_isDrawUi) {
        ImGui::Begin("Container");
        if (ImGui::Button("quit")) {
            this->m_isDrawUi = false;
        }
        this->DrawBoxUi(std::string("Box"));
        ImGui::End();
    } else {
        this->releaseEmptyItems();
    }
}

#include "Generator.h"
//#include "../../Net/NetEnergy/NetEnergy.h"
#include "../../Net/NetGenerator/NetGenerator.h"

Generator::Generator(std::string name, GameObject * parent, b2Vec2 size, b2Vec2 nodePos, double hp, float generatorSpeed, float energyMax) :
    Entity(name, "Generator", parent, nodePos, hp)
{
    this->m_netEnergy = new NetGenerator(generatorSpeed, energyMax);
    this->m_isDrawUi = false;

    sf::Texture * generatorTexture = ResourceManager::GetTexture(std::string("generator"));
    generatorTexture->setSmooth(true);

    m_mainShape = CreateRectangleShape(size, generatorTexture);
}

void Generator::onFace(Person *person)
{
    Log::setLevel(LOG_LEVEL_INFO);
    Log::printLog("[Generator]person look Generator\n");
    this->m_isDrawUi = !this->m_isDrawUi;
}

void Generator::UpdateSelf(sf::Time &dt)
{
    this->m_netEnergy->UpdateSelf(dt);
}

 void Generator::DrawUiSelf()
 {
     if (this->m_isDrawUi) {
	 ImGui::Begin("Generator");
	 if (ImGui::Button("quit")) {
	     this->m_isDrawUi = false;
	 }
	 auto netGenerator = static_cast<NetGenerator *>(this->m_netEnergy);
	 ImGui::Text("Speed: %f", netGenerator->getSpeed());
	 ImGui::Text("Energy: %f", netGenerator->getSaveEnergy());
	 ImGui::End();
     }
 }


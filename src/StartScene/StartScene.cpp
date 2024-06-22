#include "StartScene.h"
#include <cstdlib>
#include <ctime>
//#define random(a, b) (rand() % (b - a + 1) + a)
#include "../MainScene/MainScene.h"

StartScene::StartScene() : Scene(std::string("StartScene")) {}

StartScene::~StartScene() {}

StartScene * StartScene::create()
{
    StartScene * scene = new StartScene();
    scene->init();
    return scene;
}

void StartScene::init()
{
    ResourceManager::setResourcePath(std::string("./resource/"));
    ResourceManager::LoadFontFromFile("yudit.ttf", "yudit");
    ImGui::GetIO().Fonts->Clear();
    ImGui::GetIO().Fonts->AddFontFromFileTTF("./resource/font/yudit.ttf", 30.f);
    ImGui::SFML::UpdateFontTexture();
}

void StartScene::DrawUiSelf()
{
    auto windowSize = Graphic::getWindowSize();
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImVec2(windowSize.x, windowSize.y));
    ImGui::Begin("MainPage", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
    if (ImGui::Button("Start", ImVec2(windowSize.x, windowSize.y / 2))) {
        auto MainScene = MainScene::create();
        SceneManager::pop_();
        SceneManager::SetRunScene(MainScene);
    }
    if (ImGui::Button("End", ImVec2(windowSize.x, windowSize.y / 2))) {
        Graphic::Close();
    }
    ImGui::PopFont();
    ImGui::End();
}

void StartScene::UpdateSelf(sf::Time &dt)
{
}

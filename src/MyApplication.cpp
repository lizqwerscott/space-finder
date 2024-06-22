/*
*Test The Applicaton
 */

#include "MyApplication.h"
#include "slt/AllSub.h"
// #include "MainScene/MainScene.h"
#include "StartScene/StartScene.h"

MyApplication::MyApplication(int argc, char * argv[]) :
    Application(argc, argv)
{

}

MyApplication::~MyApplication()
{

}

void MyApplication::init()
{
    Graphic::init();
    Math::init(Graphic::getWindowSize());
    auto StartScene = StartScene::create();
    // auto MainScene = MainScene::create();

    SceneManager::SetRunScene(StartScene);
}

void MyApplication::end()
{

}

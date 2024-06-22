#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "slt/AllSub.h"

using namespace slt;

/**
 * @brief      Class for my slt scene.
 */
class MainScene : public Scene
{
public:
    MainScene();
    ~MainScene();
public:
    static MainScene * create();
    virtual void init() override;
    virtual void UpdateSelf(sf::Time &dt) override;
    virtual void DrawUiSelf() override;
private:
    b2Vec2 speed;
};

#endif

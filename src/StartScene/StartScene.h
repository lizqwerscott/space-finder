#ifndef STARTSCENE_H
#define STARTSCENE_H

#include "slt/AllSub.h"

using namespace slt;

class StartScene : public Scene
{
public:
    StartScene();
    ~StartScene();
public:
    static StartScene * create();
    virtual void init() override;
    virtual void UpdateSelf(sf::Time &dt) override;
    virtual void DrawUiSelf() override;
private:
};

#endif

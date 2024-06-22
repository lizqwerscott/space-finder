#ifndef BIOLOGICAL_H
#define BIOLOGICAL_H

#include "../Entity.h"

using namespace slt;

class Biological : public Entity
{
public:
    Biological(std::string name, GameObject * parent, b2Vec2 nodePos = b2Vec2(0, 0), double hp = 1);
    ~Biological();
};

#endif /* BIOLOGICAL_H */

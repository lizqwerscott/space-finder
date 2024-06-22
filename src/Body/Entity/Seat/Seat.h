#ifndef SEAT_H
#define SEAT_H

#include "../Entity.h"

class Seat : public Entity
{
public:
    Seat(std::string name, GameObject * parent, b2Vec2 nodePos, double hp = 20);
    virtual ~Seat();
public:
    virtual void onFace(Person * person) override;
    virtual void UpdateSelf(sf::Time &dt) override;
    virtual void DrawSelf() override;
public:
    bool isHavePerson();
private:
    void move(int direction, float force);
public:
    Person * m_person = nullptr;
    b2Vec2 m_pos;
};

#endif /* SEAT_H */

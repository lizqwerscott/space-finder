#ifndef COMPUTER_H
#define COMPUTER_H

#include "../Entity.h"
#include <vector>

class Thruster;
class Seat;
class Gyro;

class Computer : public Entity
{
public:
    Computer(std::string name, GameObject * parent, b2Vec2 nodePos, double hp = 30);
    virtual ~Computer();
public:
    virtual void onFace(Person * person) override;
public:
    void addControl(Entity * entity);
public:
    virtual void UpdateSelf(sf::Time &dt) override;
    virtual void DrawUiSelf() override;
private:
    //推进器 其他
    std::vector<Thruster *> m_thrusters;
    Seat * m_seat = nullptr;
    void move(int direction, float force);
public:
    static Computer * findSelf(int id);
    static void push(int computerId, int id, int force);
    static void sendSignalString(int computerId, std::string data);

    //static void move(int direction, float force);
    static void rotate(float angle);
private:
    Gyro * gyro;
};

#endif /* COMPUTER_H */

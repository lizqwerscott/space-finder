#ifndef PERSON_H
#define PERSON_H

#include "Biological.h"
#include "slt/utils.h"

class Item;
//class Clothes;
//class Hat;
//class Gloves;
//class Coat;
//class Pants;
//class Shoes;
class Bag;
class FindRayCastCallback;
class BoxBase;
class ToolBox;


class Person : public Biological
{
public:
    Person(std::string name, GameObject * parent, PhysicalWorld * world, b2Vec2 nodePos = b2Vec2(0, 0));
    ~Person();
public:
    virtual void init() override;
public:
    void useHand(b2Vec2 mouseClick);
    void rightClick(b2Vec2 mouseClick);
    bool handP() {return m_tHand != nullptr;}
    Item * getHand();
public:
    void useFace(PhysicalWorld * world);

    bool isInHand() {return m_faceFraction <= 3.309 && (m_MousePos - GetPosition()).Length() <= 10;}
    bool isInSelected() {return (m_MousePos.Length() - GetPosition().Length()) <= 10;}
    bool isHaveSelected() {return m_faceFixture != nullptr && m_faceEntity != nullptr;}
    b2Vec2 getFace() {return m_face;}
    float getFaceFraction() {return m_faceFraction;}
    Entity * getFaceEntity() {return m_faceEntity;}
    b2Fixture * getFaceFixture() {return m_faceFixture;}
public:
    void wearBag(Bag *bag);
    Bag * getBag() {return m_tBackPack;}
public:
    void move(int direction/*0 or 1*/, float force);
    void rotate(float angle);
    void drink(Item * drink);
    void eat(Item * food);
    void wear(Item * clothes);
    bool equip(Item * tool);
public:
    virtual void DrawUiSelf() override;
    virtual void DrawSelf() override;
public:
    virtual void UpdateSelf(sf::Time &dt) override;
public:
    b2Vec2 getMousePos() {return m_MousePos;}
private:
    bool m_rayCastP = false;
    FindRayCastCallback * m_findRayCastCallBack;
    b2Vec2 m_MousePos;
    b2Vec2 m_face; //mouse place
    Entity * m_faceEntity = nullptr;
    b2Fixture * m_faceFixture = nullptr;
    float m_faceFraction = 0;
public:
    bool m_SpeedAdjust;
public:
    bool m_tHandSelected = false;
private:
    //self item tools
    //hand
    //Item * m_tHand = nullptr;
    ToolBox * m_tHand = nullptr;
    int selectI = 0;
    //Backpack
    Bag * m_tBackPack = nullptr;
    //clothes
    //Hat * m_cHead = nullptr;

    //Gloves * m_cLeftHand = nullptr; //only put clothes
    //Gloves * m_cRightHand = nullptr; //only pub clothes

    // Coat * m_cBody = nullptr;
    //
    // Pants * m_cLeg;
    //
    // Shoes * m_cLeftFoot = nullptr;
    // Shoes * m_cRightFoot = nullptr;

    //Attributes
    double m_water;
    double m_food;
private:
    //Temp
    PhysicalWorld * m_world;
friend class FindRayCastCallback;
};
class QueryCallBack : public b2QueryCallback
{
public:
    bool ReportFixture(b2Fixture * fixture)
    {
        return true;
    }

};

class FindRayCastCallback : public b2RayCastCallback
{
public:
    FindRayCastCallback(Person * person) : m_person(person) {}
    ~FindRayCastCallback() {}
public:
    float ReportFixture(b2Fixture * fixture, const b2Vec2& point, const b2Vec2& normal, float fraction)
    {
        Entity * entity = reinterpret_cast<Entity *>(user_data_convert(fixture->GetUserData().pointer, 1));
        m_person->m_faceFixture = fixture;
        m_person->m_faceEntity = entity;
        m_person->m_faceFraction = fraction;
        return 0;
    }
public:
    Person * m_person;
};

#endif /* PERSON_H */

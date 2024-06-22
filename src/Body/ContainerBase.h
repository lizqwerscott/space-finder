#ifndef CONTAINERBASE_H
#define CONTAINERBASE_H

#include <string>

class Item;

class ContainerBase
{
public:
    ContainerBase(double volume, double quality);
    virtual ~ContainerBase() {}
public:
    virtual void DrawBoxUi(std::string name, int row = 1, int column = 3) = 0;
public:
    virtual bool addItem(Item * item) = 0;
    virtual Item * getItem(std::string name) = 0;
    virtual bool transferItem(ContainerBase * target, std::string name, int number) = 0;
public:
    virtual bool isEmpty() = 0;
public:
    double getNowVolume();
    double getNowQuality();
    double getMaxVolume();
    double getMaxQuality();
    void setMaxVolume(double volume);
    void setMaxQuality(double quality);
protected:
    double m_maxVolume;
    double m_maxQuality;
    double m_nowVolume = 0;
    double m_nowQuality = 0;
};

#endif /* CONTAINERBASE_H */

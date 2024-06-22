#include "Bag.h"


Bag::Bag(std::string name, double volume, double quality, double maxVolume, double maxQuality) :
    Item(name, "Bag", volume, quality),
    BoxBase(maxVolume, maxQuality)
{
}

Bag::~Bag() {}

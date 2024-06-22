#ifndef BULLETI_H
#define BULLETI_H

#include "../Consume.h"

class BulletI : public Consume
{
public:
    BulletI(std::string name, double volume, double quality);
    ~BulletI() {
        //printf("%s dead\n", this->getName().c_str());
    }
};

#endif /* BULLETI_H */


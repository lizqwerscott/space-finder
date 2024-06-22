#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include "slt/Application.h"

using namespace slt;

class MyApplication : public Application
{
public:
    MyApplication(int argc, char * argv[]);
    ~MyApplication();
public:
    virtual void init() override;
    virtual void end() override;
};

#endif

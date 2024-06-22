#ifndef NETWIRE_H
#define NETWIRE_H

#include "../NetControl/NetControl.h"

class NetWire : public NetControl
{
public:
    NetWire();
    virtual ~NetWire();
public:
    void passSignal(NetControl * sendControl, DeviceSignal &data);
};

#endif

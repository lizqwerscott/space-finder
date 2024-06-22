#ifndef NETCONTROLDEVICE_H
#define NETCONTROLDEVICE_H

#include "../NetControl/NetControl.h"
#include <map>

/*
  [summary]
  问题，信号传递到设备就会停止，而不会传递下去。

 */
class NetControlDevice : public NetControl
{
public:
    NetControlDevice(std::string _id);
    virtual ~NetControlDevice();
public:
    virtual void UpdateSelf(sf::Time &dt) override;
public:
    void sendSignal(DeviceSignal &data, std::string id = "ALL");
    void reciveSignal(DeviceSignal &data);
public:
    void subscribeRecive(DeviceSignalType type, SignalReciveFunction fun);
private:
    std::map<DeviceSignalType, std::vector<SignalReciveFunction>> subscribeRecives;
    std::string id;
};

#endif

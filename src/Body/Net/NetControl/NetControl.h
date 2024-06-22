#ifndef NETCONTROL_H
#define NETCONTROL_H

#include "../Net.h"

class Entity;

enum DeviceSignalType {
    Bool,
    String,
    Number,
    Json
};

struct DeviceSignalData
{
    DeviceSignalType type;
};

struct DeviceSignalDataBool : public DeviceSignalData
{
    bool data;
    DeviceSignalDataBool() { this->type = DeviceSignalType::Bool; }
};

struct DeviceSignalDataString : public DeviceSignalData
{
    std::string data;
    DeviceSignalDataString() { this->type = DeviceSignalType::String; }
};

struct DeviceSignalDataNumber : public DeviceSignalData
{
    double data;
    DeviceSignalDataNumber() { this->type = DeviceSignalType::Number; }
};

struct DeviceSignalDataJson : public DeviceSignalData
{
    std::string data;
    DeviceSignalDataJson() { this->type = DeviceSignalType::Json; }
};

struct DeviceSignal
{
    Entity * sender = nullptr;
    DeviceSignalData * data = nullptr;
    DeviceSignalData * res = nullptr;
};

typedef std::function<void (DeviceSignal &)> SignalReciveFunction;


class NetControl : public Net
{
public:
    NetControl(std::string typeName);
    virtual ~NetControl();
public:
    std::string m_controlTypeName;
};

#endif

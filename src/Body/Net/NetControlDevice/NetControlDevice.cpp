#include "NetControlDevice.h"
#include "../NetWire/NetWire.h"

NetControlDevice::NetControlDevice(std::string _id) : NetControl("device"), id(_id)
{

}

NetControlDevice::~NetControlDevice()
{
    this->subscribeRecives.clear();
}

void NetControlDevice::UpdateSelf(sf::Time &dt)
{

}

void NetControlDevice::sendSignal(DeviceSignal & data, std::string id)
{
    for (auto net : this->m_connectNets) {
	if (net->m_typename == "NetControl") {
	    auto controlNet = static_cast<NetControl *>(net);
	    if (controlNet->m_controlTypeName == "wire") {
		auto wire = static_cast<NetWire *>(controlNet);
		wire->passSignal(this, data);
	    }

	    if (controlNet->m_controlTypeName == "device") {
		auto device = static_cast<NetControlDevice *>(controlNet);
		if (id == "ALL") {
		    device->reciveSignal(data);
		} else {
		    if (device->id == id) {
			device->reciveSignal(data);
		    }
		}
	    }
	}
    }
}

void NetControlDevice::reciveSignal(DeviceSignal & data)
{
    auto funs = this->subscribeRecives[data.data->type];
    for (auto fun : funs) {
	fun(data);
    }
}

void NetControlDevice::subscribeRecive(DeviceSignalType type, SignalReciveFunction fun)
{
    this->subscribeRecives[type].push_back(fun);
}

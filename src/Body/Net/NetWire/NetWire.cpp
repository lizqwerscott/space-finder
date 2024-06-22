#include "NetWire.h"
#include "../NetControlDevice/NetControlDevice.h"

NetWire::NetWire() : NetControl("wire")
{

}

NetWire::~NetWire()
{

}

void NetWire::passSignal(NetControl * sendControl, DeviceSignal & signal)
{
    for (auto net : this->m_connectNets) {
	if (net->m_typename == "NetControl") {
	    auto control = static_cast<NetControl *>(net);
	    if (control != sendControl) {
		if (control->m_controlTypeName == "device") {
		    auto device = static_cast<NetControlDevice *>(control);
		    device->reciveSignal(signal);
		}
		if (control->m_controlTypeName == "wrie") {
		    auto wire = static_cast<NetWire *>(control);
		    wire->passSignal(this, signal);
		}

	    }
	}
    }
}

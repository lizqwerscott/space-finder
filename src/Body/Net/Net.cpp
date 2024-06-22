#include "Net.h"

Net::Net(const std::string &_typename) :
    m_typename(_typename)
{
    connectAnotherAfterCallBack = [](Net * net2) -> void {
    };
}

Net::~Net()
{
    this->m_connectNets.clear();
}

void Net::connectAnother(Net *net1, Net *net2)
{
    if (!net1->containNetp(net2) && !net2->containNetp(net1)) {
	net1->m_connectNets.push_back(net2);
	net2->m_connectNets.push_back(net1);

	net1->connectAnotherAfterCallBack(net2);
	net2->connectAnotherAfterCallBack(net1);
    }
}

bool Net::containNetp(Net *net)
{
    Net * temp = nullptr;
    for (int i = 0; i < (int)this->m_connectNets.size(); ++i) {
	temp = this->m_connectNets[i];
	if (temp == net) {
	    return true;
	}
    }
    return false;
}

#ifndef NET_H
#define NET_H
//Resource Net or other

#include <slt/AllSub.h>

using namespace slt;

class Net
{
public:
    Net(const std::string &_typename);
    virtual ~Net();
public:
    static void connectAnother(Net * net1, Net * net2);
public:
    bool containNetp(Net * net);
    virtual void UpdateSelf(sf::Time &dt) {}
public:
    std::vector<Net *> m_connectNets;
    std::string m_typename;

    std::function<void (Net *)> connectAnotherAfterCallBack;
};

#endif /* NET_H */

#ifndef NETMANAGER_H
#define NETMANAGER_H

class NetManager
{
public:
    NetManager * GetInstance();
    void Destory();
private:
    NetManager();
    virtual ~NetManager();
};

#endif

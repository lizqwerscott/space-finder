#include "ContainerBase.h"

ContainerBase::ContainerBase(double volume, double quality) :
    m_maxVolume(volume),
    m_maxQuality(quality)
{
}

double ContainerBase::getNowVolume()
{
    return m_nowVolume;
}

double ContainerBase::getNowQuality()
{
    return m_nowQuality;
}

double ContainerBase::getMaxVolume()
{
    return m_maxVolume;
}

double ContainerBase::getMaxQuality()
{
    return m_maxQuality;
}

void ContainerBase::setMaxVolume(double volume)
{
    m_maxVolume = volume;
}

void ContainerBase::setMaxQuality(double quality)
{
    m_maxQuality = quality;
}


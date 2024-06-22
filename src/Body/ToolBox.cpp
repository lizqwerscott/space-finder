#include "ToolBox.h"
#include "Item/Item.h"
#include "ItemTManager.h"

ToolBox::ToolBox(double volume, double quality) :
    ContainerBase(volume, quality)
{
}

ToolBox::~ToolBox()
{
    if (m_container != nullptr) {
        delete m_container;
        m_container = nullptr;
    }
}

void ToolBox::DrawBoxUi(std::string name, int row, int column)
{
    if (ImGui::BeginTable(name.c_str(), column, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings)) {
        ImGui::TableSetupColumn(name.c_str());
        char now[10];
        char max[10];
        sprintf(now, "%.1f", m_nowVolume);
        sprintf(max, "%.1f", m_maxVolume);
        std::string volume = std::string(now) + " / " + std::string(max);
        sprintf(now, "%.1f", m_nowQuality);
        sprintf(max, "%.1f", m_maxQuality);
        std::string quality = std::string(now) + " / " + std::string(max);
        ImGui::TableSetupColumn(volume.c_str());
        ImGui::TableSetupColumn(quality.c_str());
        ImGui::TableHeadersRow();
        if (m_container != nullptr) {
            std::string item = m_container->getName();
            ImGui::TableNextColumn();
            ImGui::Button(item.c_str());
            if (ImGui::IsItemActive()) {
                ItemTManager::drag(this, item);
            } else {
                if (ItemTManager::isDrag()) {
                    ItemTManager::disDrag();
                }
            }
        } else {
            ImGui::TableNextColumn();
            ImGui::Button(std::string("Null").c_str());
        }
        ImGui::EndTable();
    }
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem)) {
        if (ItemTManager::isDrag()) {
            ItemTManager::hoveredBox(this);
        }
    } else {
        if (ItemTManager::isDrag()) {
            ItemTManager::disHoveredBox(this);
        }
    }
}

bool ToolBox::addItem(Item *item)
{
    bool qualityP = item->getQuality() <= this->m_maxQuality - this->m_nowQuality;
    bool volumeP = item->getVolume() <= this->m_maxVolume - this->m_nowVolume;
    bool addP = qualityP && volumeP && (m_container == nullptr);
    if (addP) {
        m_container = item;
        this->m_nowQuality += item->getQuality();
        this->m_nowVolume += item->getVolume();
    }
    return addP;
}

Item * ToolBox::getItem(std::string name)
{
    if (name != "" && name != m_container->getName()) {
        return nullptr;
    }
    return m_container;
}

bool ToolBox::transferItem(ContainerBase *target, std::string name, int number)
{
    if (m_container != nullptr) {
        if (target->addItem(m_container)) {
            this->m_nowQuality -= m_container->getQuality();
            this->m_nowVolume -= m_container->getVolume();
            m_container = nullptr;
            return true;
        }
    }
    return false;
}

bool ToolBox::isEmpty()
{
    return m_container == nullptr;
}

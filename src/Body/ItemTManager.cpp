#include "ItemTManager.h"
#include "BoxBase.h"

ItemTManager * itemTManager = nullptr;

void ItemTManager::Create()
{
    if (itemTManager == nullptr) {
        itemTManager = new ItemTManager();
    }
}

void ItemTManager::Destory()
{
    if (itemTManager != nullptr) {
        delete itemTManager;
        itemTManager = nullptr;
    }
}

void ItemTManager::drag(ContainerBase *box, std::string name)
{
    //printf("drag: %s\n", name.c_str());
    itemTManager->m_isDrag = true;
    itemTManager->m_box = box;
    itemTManager->m_dragName = name;
}

void ItemTManager::disDrag()
{
    if (itemTManager->m_lastHoveredBox != nullptr && !ImGui::IsMouseDragging(0)) {
    }
    if (!ImGui::IsMouseDragging(0)) {
        if (itemTManager->m_lastHoveredBox != nullptr) {
            itemTManager->m_box->transferItem(itemTManager->m_lastHoveredBox, itemTManager->m_dragName, 1);
            itemTManager->m_isDrag = false;
            itemTManager->m_box = nullptr;
            itemTManager->m_dragName = "";
            itemTManager->m_lastHoveredBox = nullptr;
        }
        itemTManager->m_isDrag = false;
    } else {
        ImVec2 mousePos = ImGui::GetMousePos();
        ImGui::GetForegroundDrawList()->AddText(ImVec2(mousePos.x + 10, mousePos.y + 10), ImGui::GetColorU32(ImGuiCol_Button), itemTManager->m_dragName.c_str());
    }
}

bool ItemTManager::isDrag()
{
    return itemTManager->m_isDrag;
}

void ItemTManager::hoveredBox(ContainerBase *box)
{
    if (box != itemTManager->m_lastHoveredBox && box != itemTManager->m_box) {
        itemTManager->m_lastHoveredBox = box;
        Log::setLevel(LOG_LEVEL_INFO);
        Log::printLog("hoveredBox\n");
    }
}

void ItemTManager::disHoveredBox(ContainerBase *box)
{
    if (box == itemTManager->m_lastHoveredBox) {
        itemTManager->m_lastHoveredBox = nullptr;
    }
}

#include "Framework.h"

EditTile::EditTile(Vector2 size, InstanceData* data)
    : BoxCollider(size), instanceData(data)
{
}

EditTile::~EditTile()
{
}

void EditTile::Update()
{
    if (KEY->Press(VK_LBUTTON))
    {
        if (IsPointCollision(mousePos))
        {
            instanceData->curFrame = MapEditor::GetSelectFrame();

            EventManager::Get()->ExcuteEvent("UpdateInstance");
        }        
    }
}

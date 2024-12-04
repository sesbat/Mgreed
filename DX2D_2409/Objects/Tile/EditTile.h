#pragma once

class EditTile : public BoxCollider
{
public:
    EditTile(Vector2 size, InstanceData* data);
    ~EditTile();

    void Update();
    void SetDragging(bool isDragging) { this->isDragging = isDragging; }
    bool IsDragging() { return isDragging; }
private:
    InstanceData* instanceData;
    bool isDragging;
};
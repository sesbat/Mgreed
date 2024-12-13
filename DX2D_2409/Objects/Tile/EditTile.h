#pragma once

class EditTile : public BoxCollider
{
public:
    EditTile(Vector2 size, InstanceData* data);
    ~EditTile();

    void Update();
    void SetInstanceData(Vector2 curFrame);
    InstanceData* GetInstanceData() { return instanceData; }
private:
    InstanceData* instanceData;    
};
#pragma once

class SokobanPlayer;
class MapEditor : public Transform
{
public:
    MapEditor();
    ~MapEditor();

    void PreRender();
    void Update();
    void Render();
    void Edit();

    void Save(const string& filePath);
    void Load(const string& filePath);

    static Vector2 GetSelectFrame() { return selectFrame; }

private:
    void DragTile();

    void CreateTiles();
    void LoadTextures();
    void RenderButtons();
    void PlaceCollisionTile();
    void UpdateInstanceData();
    void PlayerCollision();
private:
    UINT width = 10, height = 10;

    Quad* quad;
    Quad* selectImage = nullptr;

    vector<InstanceData> instances;
    VertexBuffer* instanceBuffer;

    vector<EditTile*> editTiles;
    vector<CollisionTile*> collisionTiles;
    vector<Texture*> EditTextures;
    vector<Texture*> collisionTextures;

    static Vector2 selectFrame;

    Texture* collisionSelectedTexture = nullptr;
    bool collisionMode = false; 

    SokobanPlayer* player;
};
#pragma once

class EditorScene : public Scene
{
private:
    const UINT WIDTH = 10;
    const UINT HEIGHT = 10;
public:
    EditorScene();
    ~EditorScene();

    void Update() override;
    void Render() override;
    void PostRender() override;

    void SaveMap(string filePath);
    void LoadMap(string filePath);

private:
    //vector<ImageObject*> tiles;

    ImageObject* imageObject;

    vector<Button*> tileButtons;

    vector<Matrix> instances;
    VertexBuffer* instanceBuffer;

    bool isDragging = false; 
    int selectedTileIndex = -1; 

    Vector2 mouseOffset; 
    Vector2 tileSize;
};
#pragma once

class TileMapScene : public Scene
{
public:
    TileMapScene();
    ~TileMapScene();

    void PreRender()override;
    void Update() override;
    void Render() override;
    void PostRender() override;

private:
    MapEditor* mapEditor;
};
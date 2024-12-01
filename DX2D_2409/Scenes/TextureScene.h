#pragma once

class TextureScene : public Scene
{
public:
    TextureScene();
    ~TextureScene();

    void Update() override;
    void Render() override;
    void PostRender() override;

private:
    Quad* rect;
};
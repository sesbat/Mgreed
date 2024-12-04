#pragma once

class InstancingScene : public Scene
{
private:
    const UINT SIZE = 1000;
    const UINT WIDTH = 10;
    const UINT HEIGHT = 10;
public:
    InstancingScene();
    ~InstancingScene();

    void Update() override;
    void Render() override;
    void PostRender() override;

public:
    //vector<Quad*> quads;
    Quad* quad;

    vector<Matrix> instances;
    VertexBuffer* instanceBuffer;
};
#pragma once

class AcadeScene : public Scene
{
public:
    AcadeScene();
    ~AcadeScene();

    void Update() override;
    void Render() override;
    void PostRender() override;

private:
    ImageObject* land;
    Mario* mario;
};
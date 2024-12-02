#pragma once

class AnimationScene : public Scene
{
public:
    AnimationScene();
    ~AnimationScene();

    void Update() override;
    void Render() override;
    void PostRender() override;

private:
    Robot* robot;
    Boss* boss;
};
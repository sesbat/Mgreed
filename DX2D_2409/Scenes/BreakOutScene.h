#pragma once

class BreakOutScene : public Scene
{
public:
    BreakOutScene();
    ~BreakOutScene();

    void Update() override;
    void Render() override;
    void PostRender() override;

private:
    ImageObject* background;
    ControlBar* controlBar;
    Ball* ball;
};
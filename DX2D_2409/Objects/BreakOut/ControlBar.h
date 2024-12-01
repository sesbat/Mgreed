#pragma once

class ControlBar : public ImageObject
{
private:
    const float FRAME_INTERVAL = 0.1f;

public:
    ControlBar();
    ~ControlBar();

    void Update();

    void SetBrackground(BoxCollider* background) { this->background = background; }
private:
    void Control();
    void UpdateFrame();

private:
    BoxCollider* background;
    float speed = 200.0f;   

    int curFrame = 0;
    float frameTime = 0.0f;
};
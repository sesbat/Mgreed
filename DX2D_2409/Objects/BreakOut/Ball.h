#pragma once

class Ball : public ImageObject
{
public:
    Ball();
    ~Ball();

    void Update();
    void Render();

    void HorizontalCollision() { direction.x *= -1.0f; }
    void VerticalCollision() { direction.y *= -1.0f; }

    void SetControlBar(BoxCollider* controlBar) { this->controlBar = controlBar; }
    void SetBackground(BoxCollider* background) { this->background = background; }

    void SetReady() { isPlay = false; }

private:
    void Control();
    void Move();

    void CollisionBG();
    void CollisionBall();

private:
    float speed = 250.0f;
    Vector2 direction = { 0, 1.0f };

    bool isPlay = false;

    BoxCollider* controlBar;
    BoxCollider* background;
};
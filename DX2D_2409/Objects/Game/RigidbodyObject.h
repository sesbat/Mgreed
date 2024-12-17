#pragma once

class RigidbodyObject : public BoxCollider
{
protected:
    const float GRAVITY = 980.0f;    
    const float MOVE_SPEED = 200.0f;
    const float ACCELATION = 800.0f;
    const float DECELELATION = 4.0f;

public:
    RigidbodyObject();
    ~RigidbodyObject();

    void Update();

    void HorizontalMove(bool isRight);
    virtual void Gravity();

    void SetVelocityY(float velocityY) { velocity.y = velocityY; }
    void SetVelocity(Vector2 velocity) { this->velocity = velocity; }
    void AddVelocity(Vector2 velocity) { this->velocity += velocity; }
protected:
    float speed = 100.0f;
    Vector2 velocity;
};
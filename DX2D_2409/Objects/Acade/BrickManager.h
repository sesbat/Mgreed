#pragma once

class BrickManager : public Singleton<BrickManager>
{
private:
    friend class Singleton;

    BrickManager();
    ~BrickManager();

public:
    void Render();

    GameMath::Direction Push(IN BoxCollider* collider, OUT BoxCollider*& outBrick);

private:
    vector<ImageObject*> bricks;
};
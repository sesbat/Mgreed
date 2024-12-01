#pragma once

class CollisionScene : public Scene
{
public:
    CollisionScene();
    ~CollisionScene();

    void Update() override;
    void Render() override;

private:
    vector<Collider*> colliders;

    // Scene을(를) 통해 상속됨
    void PostRender() override;
};
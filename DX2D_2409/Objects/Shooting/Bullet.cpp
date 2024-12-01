#include "Framework.h"
#include "Bullet.h"

Bullet::Bullet() : Quad(L"Textures/Shooter/playerBullet.png")
{
    isActive = false;

    collider = new CircleCollider(size.x * 0.5f);
    collider->SetParent(this);
}

Bullet::Bullet(wstring textureFile, Vector2 maxFrame)
    : Quad(textureFile, Vector2(), Vector2(1 / maxFrame.x, 1 / maxFrame.y))
{
    isActive = false;

    collider = new CircleCollider(size.x * 0.5f);
    collider->SetParent(this);
}

Bullet::~Bullet()
{
    delete collider;
}

void Bullet::Update()
{
    if (!isActive) return;

    //pos.y += moveSpeed;
    pos += dir * moveSpeed * DELTA;

    if (pos.y > SCREEN_HEIGHT)
        isActive = false;

    UpdateWorld();
    collider->UpdateWorld();
}

void Bullet::Render()
{
    GameObject::Render();
    collider->Render();
}

void Bullet::Fire(Float2 pos, Vector2 dir, Float4 color)
{
    this->pos = pos;
    UpdateWorld();
    collider->UpdateWorld();

    this->dir = dir.Normalized();
    material->SetColor(color);
    isActive = true;

    rot.z = dir.Angle() - PI / 2;
}

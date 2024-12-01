#include "Framework.h"

BulletManager* BulletManager::instance = nullptr;

BulletManager::BulletManager()
{
    bullets.resize(BULLET_SIZE);

    for (Bullet*& bullet : bullets)
    {
        bullet = new Bullet();
        bullet->SetActive(false);
    }
}

BulletManager::~BulletManager()
{
    for (Bullet* bullet : bullets)
    {
        delete bullet;
    }
}

void BulletManager::Update()
{
    for (Bullet* bullet : bullets)
    {
        bullet->Update();
    }
}

void BulletManager::Render()
{
    for (Bullet* bullet : bullets)
    {
        bullet->Render();
    }
}

void BulletManager::Fire(const Vector2& pos, const Vector2& dir, string tag, Float4 color)
{
    for (Bullet* bullet : bullets)
    {
        if (!bullet->IsActive())
        {
            bullet->Fire(pos, dir, color);
            bullet->SetTag(tag);
            return;
        }
    }
}

void BulletManager::Collision(Player* player, string tag)
{
    for (Bullet* bullet : bullets)
    {
        if (bullet->GetTag() == "Enemy" && bullet->GetCollider()->IsCollision(player->GetCollider()))
        {
            bullet->SetActive(false);
            player->Damage();
        }
    }
}

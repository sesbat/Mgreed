#pragma once

class BulletManager
{
private:
    const UINT BULLET_SIZE = 50;

private:
    BulletManager();
    ~BulletManager();

public:
    void Update();
    void Render();

    void Fire(const Vector2& pos, const Vector2& dir, string tag, Float4 color = Float4(1, 1, 1, 1));

    void Collision(class Player* player, string tag);

public:
    //static BulletManager* Get()
    //{
    //    static BulletManager instance;
    //    return &instance;
    //}

    static BulletManager* Get()
    {
        if (instance == nullptr)
            instance = new BulletManager();

        return instance;
    }
    static void Delete()
    {
        delete instance;
    }

private:
    vector<Bullet*> bullets;

private:
    static BulletManager* instance;
};
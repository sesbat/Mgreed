#include "Framework.h"

Mario::Mario()
{
    image = new Quad(L"Textures/Acade/mario.png",
        Vector2(6.0f / 8.0f, 3.0f / 4.0f), Vector2(7.0f / 8.0f, 1));
    image->SetParent(this);
    image->GetMaterial()->SetMaxFrame(8, 4);

    UpdateSize(image->GetSize());

    pos = CENTER;
    pos.x += 100;
    UpdateWorld();
}

Mario::~Mario()
{
}

void Mario::Update()
{
    Move();
    Jump();

    RigidbodyObject::Update();

    CollisionBrick();
    Land();    

    image->UpdateWorld();
}

void Mario::Render()
{
    image->Render();
    Collider::Render();
}

void Mario::Move()
{
    bool isMove = false;

    if (KEY->Press(VK_RIGHT))
    {
        velocity.x += ACCELATION * DELTA;
        isMove = true;
    }
    if (KEY->Press(VK_LEFT))
    {
        velocity.x -= ACCELATION * DELTA;
        isMove = true;
    }
}

void Mario::Jump()
{
    if (KEY->Down(VK_UP))
    {
        velocity.y = JUMP_POWER;
    }   
}

void Mario::Land()
{
    if (velocity.y > 0) return;

    Vector2 overlap;
    if (landCollider->IsCollision(this, &overlap))
    {
        velocity.y = 0.0f;
        Translate(Vector2::Up() * overlap.y);
    }
}

void Mario::CollisionBrick()
{
    BoxCollider* brick;
    GameMath::Direction dir = BrickManager::Get()->Push(this, brick);

    switch (dir)
    {
    case GameMath::Direction::UP:
        if(velocity.y < 0.0f)
            velocity.y = 0.0f;
        break;
    case GameMath::Direction::DOWN:
        if (velocity.y > 0)
        {
            velocity.y = 0.0f;
            brick->SetActive(false);
        }        
        break;    
    }
}

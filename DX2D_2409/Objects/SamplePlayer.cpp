#include "Framework.h"
#include "SamplePlayer.h"

SamplePlayer::SamplePlayer()
{
    landCollider = NULL;
    image = new Quad(L"Textures/Acade/mario.png",
        Vector2(6.0f / 8.0f, 3.0f / 4.0f), Vector2(7.0f / 8.0f, 1));
    image->SetParent(this);
    image->GetMaterial()->SetMaxFrame(8, 4);

    UpdateSize(image->GetSize());

    pos = CENTER;
    pos.x += 100;
    UpdateWorld();
}

SamplePlayer::~SamplePlayer()
{
}

void SamplePlayer::Update()
{
    Move();
    Jump();

    RigidbodyObject::Update();

    CheckCollider();

    image->UpdateWorld();
}

void SamplePlayer::Render()
{
    image->Render();
    Collider::Render();
}

void SamplePlayer::Move()
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

void SamplePlayer::Jump()
{
    if (KEY->Down(VK_UP))
    {
        velocity.y = JUMP_POWER;
    }
}

void SamplePlayer::CheckCollider()
{
    if (velocity.y > 0) return;

    for (size_t i = 0; i < colCount; i++)
    {
        Vector2 overlap;
        if (landCollider[i]->IsCollision(this, &overlap))
        {
            velocity.y = 0.0f;
            Translate(Vector2::Up() * overlap.y);
        }
    }
}

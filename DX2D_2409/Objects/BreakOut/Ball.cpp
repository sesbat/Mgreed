#include "Framework.h"

Ball::Ball() : ImageObject(L"Textures/Breakout/Ball.bmp")
{
}

Ball::~Ball()
{
}

void Ball::Update()
{
    CollisionBG();
    CollisionBall();
    BlockManager::Get()->CollisionBall(this);

    Control();    
    Move();        

    ImageObject::Update();
}

void Ball::Render()
{
    ImageObject::Render();
}

void Ball::Control()
{ 
    if (isPlay)
        return;
    
     pos.x = controlBar->GetPos().x;
     pos.y = controlBar->Top() + HalfSize().y;

     if (KEY->Down(VK_SPACE))
         isPlay = true ;
}

void Ball::Move()
{
    Translate(direction * speed * DELTA);
}

void Ball::CollisionBG()
{
    if (!isPlay) return;

    if (Left() <= background->Left() && direction.x < 0)
    {
        pos.x = background->Left() + HalfSize().x;
        direction.x *= -1.0f;
    }

    if (Right() >= background->Right() && direction.x > 0)
    {
        pos.x = background->Right() - HalfSize().x;
        direction.x *= -1.0f;
    }

    if (Top() >= background->Top() && direction.y > 0)
    {
        pos.y = background->Top() - HalfSize().y;
        direction.y *= -1.0f;
    }

    if (Bottom() <= background->Bottom())
    {
        SetReady();
    }
}

void Ball::CollisionBall()
{
    if (!isPlay) return;

    if (IsCollision(controlBar))
    {
        Vector2 dir = pos - controlBar->GetPos();
        direction = dir.Normalized();
    }    
}

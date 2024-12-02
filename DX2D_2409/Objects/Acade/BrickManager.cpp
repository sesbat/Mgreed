#include "Framework.h"

BrickManager::BrickManager()
{
	Vector2 stertPos = { 5,0 };
	Vector2 endPos = { 10,5 };
    bricks.push_back(new ImageObject(L"Textures/Acade/Brick.png", stertPos, endPos));
    bricks.back()->SetPos(CENTER);
    bricks.back()->Update();
    bricks.push_back(new ImageObject(L"Textures/Acade/Brick.png"));
    bricks.back()->SetPos(CENTER + Vector2::Right()* 100);
    bricks.back()->Update();
    bricks.push_back(new ImageObject(L"Textures/Acade/Brick.png"));
    bricks.back()->SetPos(CENTER + Vector2::Left() * 100 + Vector2::Down() * 50);
    bricks.back()->Update();
}

BrickManager::~BrickManager()
{
    for (ImageObject* brick : bricks)
        delete brick;
}

void BrickManager::Render()
{
    for (ImageObject* brick : bricks)
        brick->Render();
}

GameMath::Direction BrickManager::Push(IN BoxCollider* collider, OUT BoxCollider*& outBrick)
{
    Vector2 overlap;

    GameMath::Direction result = GameMath::Direction::NONE;

    for (ImageObject* brick : bricks)
    {
        if (brick->IsCollision(collider, &overlap))
        {
            outBrick = brick;

            if (overlap.x < overlap.y)//좌우 충돌
            {
                if (brick->GetGlobalPos().x > collider->GetGlobalPos().x)
                {
                    collider->Translate(Vector2::Left() * overlap.x);

                    if ((int)result > 1)
                        result = GameMath::Direction::LEFT;
                }
                else
                {
                    collider->Translate(Vector2::Right() * overlap.x);
                    if ((int)result > 1)
                        result = GameMath::Direction::RIGHT;
                }
            }
            else//상하충돌
            {
                if (brick->GetGlobalPos().y > collider->GetGlobalPos().y)
                {
                    collider->Translate(Vector2::Down() * overlap.y);
                    result = GameMath::Direction::DOWN;
                }
                else
                {
                    collider->Translate(Vector2::Up() * overlap.y);
                    result = GameMath::Direction::UP;
                }
            }
        }
    }

    return result;
}

#include "Framework.h"

Block::Block(int type)
    : ImageObject(L"Textures/BreakOut/Block.png", 6, 4),
    type(type), curHp(type)
{
    SetFrame();
}

Block::~Block()
{
}

void Block::Render()
{
    if (curHp <= 0)
        return;

    ImageObject::Render();
}

void Block::Damage()
{
    if (type == 10)
        return;

    curHp--;

    SetFrame();
}

void Block::SetFrame()
{
    float x = curHp % 4;
    float y = curHp / 4;

    if (type == 10)
    {
        image->GetMaterial()->SetCurFrame(0, 2);
    }
    else
    {
        image->GetMaterial()->SetCurFrame(x, y);
    }
}

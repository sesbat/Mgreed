#include "Framework.h"

ControlBar::ControlBar() : ImageObject(L"Textures/BreakOut/Bar.png", 1, 4)
{
    pos = { CENTER_X, SCREEN_HEIGHT * 0.1f }; 

    image->GetMaterial()->SetRemoveColor(1, 1, 1);
}

ControlBar::~ControlBar()
{
}

void ControlBar::Update()
{
    Control();
    UpdateFrame();

    ImageObject::Update();
}

void ControlBar::Control()
{
    if (KEY->Press(VK_RIGHT))
        Translate(Vector2::Right() * speed * DELTA);
    if (KEY->Press(VK_LEFT))
        Translate(Vector2::Left() * speed * DELTA);

    //if (Left() < background->Left())
    //    pos.x = background->Left() + HalfSize().x;
    //if (Right() > background->Right())
    //    pos.x = background->Right() - HalfSize().x;
    pos.x = GameMath::Clamp(background->Left() + HalfSize().x,
        background->Right() - HalfSize().x, pos.x);
}

void ControlBar::UpdateFrame()
{
    frameTime += DELTA;

    if (frameTime >= FRAME_INTERVAL)
    {
        frameTime -= FRAME_INTERVAL;

        ++curFrame %= (int)image->GetMaterial()->GetFrame().maxFrame.y;

        image->GetMaterial()->SetCurFrame(0, curFrame);
    }
}

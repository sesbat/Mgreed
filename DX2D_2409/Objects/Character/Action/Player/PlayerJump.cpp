#include "Framework.h"

PlayerJump::PlayerJump(Player* player)
	:PlayerMove(player)
{
    LoadClip("Textures/Dungreed/Character/Jump/", "JumpStart.xml", false);
    LoadClip("Textures/Dungreed/Character/Jump/", "Jumping.xml", true);
    LoadClip("Textures/Dungreed/Character/Jump/", "JumpEnd.xml", false);

    clips[START]->SetEvent(bind(&PlayerJump::EndJumpStart, this));
    clips[END]->SetEvent(bind(&Player::Land, player));
}

void PlayerJump::Update()
{
    Loop();

    /*if (curState != END)
        player->Gravity();*/
    if (curState != START && KEY->Down('W'))
    {
        SetState(START);
        player->SetVelocityY(JUMP_POWER);
    }

    PlayerMove::Update();
}

void PlayerJump::Start()
{
    curState = START;
    clips[curState]->Play();
    player->SetVelocityY(JUMP_POWER);
}

void PlayerJump::Loop()
{
    if (curState != LOOP) return;

    if (player->IsGround())
        SetState(END);
}

void PlayerJump::EndJumpStart()
{
    SetState(LOOP);
}

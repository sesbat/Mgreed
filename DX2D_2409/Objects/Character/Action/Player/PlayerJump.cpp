#include "Framework.h"

PlayerJump::PlayerJump(Player* player)
	:PlayerMove(player)
{
    LoadClip("Textures/Maple/DefaultCharacter/Jump/", "JumpStart.xml", false);
    LoadClip("Textures/Maple/DefaultCharacter/Jump/", "Jumping.xml", true);
    LoadClip("Textures/Maple/DefaultCharacter/Jump/", "JumpEnd.xml", false);

    clips[START]->SetEvent(bind(&PlayerJump::EndJumpStart, this));
    clips[END]->SetEvent(bind(&Player::OnGround, player));
}

void PlayerJump::Update()
{
    Loop();

    if (curState != END)
        player->Gravity();

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

}

void PlayerJump::EndJumpStart()
{
    SetState(LOOP);
}

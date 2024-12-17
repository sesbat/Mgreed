#include "Framework.h"

PlayerDash::PlayerDash(Player* player)
	:PlayerMove(player)
{
	LoadClip("Textures/Dungreed/Character/Jump/", "Jumping.xml", true);
}

void PlayerDash::Update()
{
	Loop();
	PlayerMove::Update();
}

void PlayerDash::Start()
{
	clips[0]->Play();
	Vector2 dir = (worldMousePos - player->GetGlobalPos()).Normalized();
	player->SetVelocity(dir * DASH_POWER);
}

void PlayerDash::Loop()
{
	if (player->IsGround())
		player->SetActionState(Player::ActionState::IDLE);
}

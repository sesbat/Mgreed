#include "Framework.h"

PlayerMove::PlayerMove(Player* player)
	:PlayerAction(player)
{
    //LoadClip("Textures/Dungreed/Character/Walk/", "Walk.xml", true);
}

void PlayerMove::Update()
{
    if (KEY->Press('A'))
        player->HorizontalMove(false);
    if (KEY->Press('D'))
        player->HorizontalMove(true);

    Action::Update();
}

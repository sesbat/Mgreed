#include "Framework.h"

PlayerRun::PlayerRun(Player* player)
	:PlayerMove(player)
{
	LoadClip("Textures/Dungreed/Character/Run/", "Run.xml", true);
}

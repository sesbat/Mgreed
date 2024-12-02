#include "Framework.h"

BossMove::BossMove(Boss* boss)
	:BossAction(boss)
{
	LoadClip(L"Textures/Mgreed/BossMove.png", 8, 1, true);
}

void BossMove::Update()
{
	Action::Update();
}

#include "Framework.h"

BossDie::BossDie(Boss* boss)
	:BossAction(boss)
{
	LoadClip(L"Textures/Mgreed/BossDie.png", 29, 1, false);
	clips[0]->SetEvent(bind(&Boss::EndDie, boss));
}

void BossDie::Update()
{
	Action::Update();
}

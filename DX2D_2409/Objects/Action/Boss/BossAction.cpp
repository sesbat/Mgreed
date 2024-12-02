#include "Framework.h"

BossAction::BossAction(Boss* boss)
	:boss(boss)
{
}

void BossAction::Update()
{
	Action::Update();
}

void BossAction::Render()
{
	Action::Render();
}


#pragma once
#include "Framework.h"

class BossAction : public Action
{
public:
	BossAction(Boss* boss);

	void Update();
	void Render();

protected:
	Boss* boss;
};
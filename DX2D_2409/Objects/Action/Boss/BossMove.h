#pragma once
class BossMove : public BossAction
{
public:
	BossMove(Boss* boss);

private:
	void Update();
};


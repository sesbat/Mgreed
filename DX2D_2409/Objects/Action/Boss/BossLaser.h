#pragma once

class BossLaser : public BossAction
{
public:
	BossLaser(Boss* boss, Robot* robot);

	void OnActiveCollider();
	void OnInactiveCollider();

	void Update();
	void Render();

	BoxCollider* GetAttackCollider() { return attackCollider; }
private:
	BoxCollider* attackCollider;

	Robot* robot;
};


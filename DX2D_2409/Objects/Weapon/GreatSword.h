#pragma once

class GreatSword : public MeleeWeapon
{
public:
	GreatSword();
	~GreatSword();

	void Attack() override;
private:
};

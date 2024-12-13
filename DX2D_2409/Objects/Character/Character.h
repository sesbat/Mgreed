#pragma once
#include "Framework.h"

class Character : public RigidbodyObject
{
public:
	Character();
	~Character();

private:
	float curHp;
	float maxHp;
	float attack;
};

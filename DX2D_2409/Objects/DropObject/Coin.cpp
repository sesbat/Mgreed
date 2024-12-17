#include "Framework.h"

Coin::Coin()
{
	action->LoadClip("Textures/Dungreed/Item/Coin/", "Coin.xml", true);
	UpdateSize(action->GetClip(0)->GetCurFrame()->GetSize());

}

Coin::~Coin()
{
}

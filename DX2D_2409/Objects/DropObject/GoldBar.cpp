#include "Framework.h"

GoldBar::GoldBar()
{
	action->LoadClip("Textures/Dungreed/Item/GoldBar/","GoldBar.xml",true);
	UpdateSize(action->GetClip(0)->GetCurFrame()->GetSize());
}

GoldBar::~GoldBar()
{
}

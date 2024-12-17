#include "Framework.h"

AED::AED()
{
	action->LoadClip("Textures/Dungreed/Item/AED/", "AED.xml", true);
	UpdateSize(action->GetClip(0)->GetCurFrame()->GetSize());

}

AED::~AED()
{
}

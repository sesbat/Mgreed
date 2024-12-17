#include "Framework.h"

BreakObject::BreakObject(wstring defaultImage)
{
	objectImage = new Quad(defaultImage);
}

BreakObject::~BreakObject()
{
	delete objectImage;
}

void BreakObject::Update()
{
	objectImage->UpdateWorld();
}

void BreakObject::Render()
{
	objectImage->Render();
}

#pragma once
#include "Framework.h"

class MapEditorScene : public Scene
{
public:
	MapEditorScene();
	~MapEditorScene();
	void Update() override;
	void Render() override;
	void PostRender() override;
private:
	MapEditor* mapEditor;
};
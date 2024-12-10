﻿#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#define WIN_START_X 0
#define WIN_START_Y 0

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define CENTER_X SCREEN_WIDTH * 0.5f
#define CENTER_Y SCREEN_HEIGHT * 0.5f

#define CENTER Vector2(CENTER_X, CENTER_Y)

#define PI 3.141592f

#define FOR(n) for(int i = 0 ; i < n ; i++)

#define DELTA Timer::Get()->GetElapsedTime()
#define KEY Keyboard::Get()
#define FONT Font::Get()
#define CAM Environment::Get()->GetMainCamera()

#include <windows.h>
#include <string>
#include <fstream>
#include <functional>
#include <assert.h>
#include <iostream>
#include <sstream>
//선형자료구조 - 삽입삭제
#include <vector>
#include <list>
#include <queue>
#include <stack>
//비선형자료구조 - 검색
//트리
#include <map>
#include <set>
//해쉬테이블
#include <unordered_map>
#include <unordered_set>


#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

//ImGui
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#pragma comment(lib, "ImGui.lib")

//DirectXTex
#include <DirectXTex/DirectXTex.h>
#pragma comment(lib, "DirectXTex.lib")

//DirectWrite
#include <d2d1_2.h>
#include <dwrite.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

using namespace std;
using namespace DirectX;

typedef XMFLOAT4 Float4;
typedef XMFLOAT3 Float3;
typedef XMFLOAT2 Float2;
typedef XMMATRIX Matrix;
typedef function<void()> Event;
typedef function<void(int)> IntParamEvent;
typedef function<void(void*)> ObjectParamEvent;

//Framework Header
#include "Framework/Math/Vector2.h"
#include "Framework/Math/GameMath.h"
#include "Framework/Math/Transform.h"

#include "Framework/Utility/Singleton.h"
#include "Framework/Utility/Timer.h"
#include "Framework/Utility/Keyboard.h"
#include "Framework/Utility/Font.h"
#include "Framework/Utility/Utility.h"
#include "Framework/Utility/BinaryWriter.h"
#include "Framework/Utility/BinaryReader.h"
#include "Framework/Utility/tinyxml2.h"

#include "Framework/Buffer/VertexBuffer.h"
#include "Framework/Buffer/ConstBuffer.h"
#include "Framework/Buffer/GlobalBuffer.h"

#include "Framework/Render/Mesh.h"
#include "Framework/Render/VertexShader.h"
#include "Framework/Render/Shader.h"
#include "Framework/Render/Texture.h"
#include "Framework/Render/Material.h"
#include "Framework/Render/Frame.h"
#include "Framework/Render/Clip.h"
#include "Framework/Render/RenderTarget.h"

#include "Framework/Environment/Camera.h"
#include "Framework/Environment/Environment.h"

//Object Header
#include "Objects/Basic/GameObject.h"
#include "Objects/Basic/Quad.h"
#include "Objects/Basic/Poly.h"

#include "Objects/Collision/Collider.h"
#include "Objects/Collision/CircleCollider.h"
#include "Objects/Collision/BoxCollider.h"
#include "Objects/Collision/LineCollider.h"

#include "Objects/Game/ImageObject.h"
#include "Objects/Game/RigidbodyObject.h"
#include "Objects/Game/Action.h"
#include "Objects/Game/Effect.h"
#include "Objects/Game/EffectManager.h"

#include "Objects/Manager/DataManager.h"
#include "Objects/Manager/EventManager.h"

#include "Objects/UI/Button.h"
#include "Objects/UI/Slider.h"

#include "Objects/Shooting/Bullet.h"
#include "Objects/Shooting/BulletManager.h"
#include "Objects/Shooting/Player.h"

#include "Objects/Acade/Mario.h"
#include "Objects/Acade/BrickManager.h"

#include "Objects/Inventory/Item.h"
#include "Objects/Inventory/Store.h"
#include "Objects/Inventory/Inventory.h"

#include "Objects/Action/Robot.h"
#include "Objects/Action/RobotAction.h"
#include "Objects/Action/RobotMove.h"
#include "Objects/Action/RobotRun.h"
#include "Objects/Action/RobotJump.h"
#include "Objects/Action/RobotMelee.h"
#include "Objects/Action/RobotShoot.h"

#include "Objects/Action/RobotDead.h"
#include "Objects/Action/Boss/Boss.h"
#include "Objects/Action/Boss/BossAction.h"
#include "Objects/Action/Boss/BossLaser.h"
#include "Objects/Action/Boss/BossDie.h"
#include "Objects/Action/Boss/BossMove.h"

#include "DataTables/FileData.h"
#include "Objects/Tile/Tile.h"
#include "Objects/Tile/Room.h"
#include "Objects/Tile/Map.h"
#include "Objects/Tile/TileLoader.h"
#include "Objects/Tile/MapEditor.h"

//Manager Header
#include "Scenes/Scene.h"
#include "Manager/SceneManager.h"
#include "Manager/GameManager.h"
#include "Manager/CollisionManager.h"
#include "Objects/SamplePlayer.h"

extern ID3D11Device* device;
extern ID3D11DeviceContext* deviceContext;
extern IDXGISwapChain* swapChain;
extern Vector2 mousePos;
extern HWND hWnd;



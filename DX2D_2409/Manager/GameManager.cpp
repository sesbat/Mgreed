#include "Framework.h"

//#include "Scenes/TutorialScene.h"
#include "Scenes/ShootingScene.h"
#include "Scenes/CollisionScene.h"
#include "Scenes/TextureScene.h"
#include "Scenes/AcadeScene.h"
#include "Scenes/BreakOutScene.h"
#include "Scenes/UIScene.h"
#include "Scenes/AnimationScene.h"
#include "Scenes/ShaderScene.h"

GameManager::GameManager()
{
    Init();

    //scene = new TutorialScene();
    //scene = new ShootingScene();
    //scene = new CollisionScene();
    //scene = new TextureScene();
    //scene = new AcadeScene();
    //scene = new BreakOutScene();
    //scene = new UIScene();
    //SceneManager::Get()->Add("Start", new UIScene());
    //SceneManager::Get()->Add("Start", new ShootingScene());
    //SceneManager::Get()->Add("Break", new BreakOutScene());
    //SceneManager::Get()->Add("Start", new AcadeScene());   
    SceneManager::Get()->Add("Start", new AnimationScene());
    //SceneManager::Get()->Add("Start", new ShaderScene());

    SceneManager::Get()->ChangeScene("Start");
}

GameManager::~GameManager()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();

    ImGui::DestroyContext();

    Environment::Delete();
    Texture::Delete();
    Shader::Delete();
    Timer::Delete();
    Keyboard::Delete();
    SceneManager::Delete();
    EventManager::Delete();
    EffectManager::Delete();
}

void GameManager::Update()
{
    Timer::Get()->Update();
    Keyboard::Get()->Update();

    Environment::Get()->Update();
    EffectManager::Get()->Update();
    SceneManager::Get()->Update();
}

void GameManager::Render()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    string fps = "FPS : " + to_string(Timer::Get()->GetFPS());    
    ImGui::Text(fps.c_str());

    Font::Get()->SetColor("White");
    Font::Get()->SetStyle("Default");

    Font::Get()->GetDC()->BeginDraw();

    Environment::Get()->Render();
    SceneManager::Get()->Render();
    EffectManager::Get()->Render();
    Environment::Get()->PostRender();
    SceneManager::Get()->PostRender();    

    Font::Get()->GetDC()->EndDraw();

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void GameManager::Init()
{
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(device, deviceContext);

    Environment::Get();
    Timer::Get();
    Keyboard::Get();
    EventManager::Get();
    EffectManager::Get();

    Font::Get()->AddColor("White", 1, 1, 1);
    Font::Get()->AddColor("Black", 0, 0, 0);
    Font::Get()->AddStyle("Default", L"�ü�ü");
    Font::Get()->AddStyle("Button", L"���� ���", 20,
        DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_FAR);    
}

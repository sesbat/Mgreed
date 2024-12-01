#include "Framework.h"
#include "UIScene.h"

UIScene::UIScene()
{
    FONT->AddStyle("Store", L"����ǹ��� �ѳ��� ���ѻ�", 30);
    FONT->AddColor("Store", 1, 0.8f, 0.5f);

    buttons.push_back(new Button());
    buttons.back()->SetPos(50, SCREEN_HEIGHT - 50);
    buttons.back()->SetEvent(bind(&UIScene::OnClickButton1, this));
    buttons.back()->SetText("Store");
    buttons.push_back(new Button());
    buttons.back()->SetPos(150, SCREEN_HEIGHT - 50);
    buttons.back()->SetEvent(bind(&UIScene::OnClickButton2, this));
    buttons.back()->SetText("Inven");

    DataManager::Get();

    store = new Store();   
    store->SetActive(false);

    inven = new Inventory();
    inven->SetActive(false);
}

UIScene::~UIScene()
{
    for (Button* button : buttons)
        delete button;

    delete store;
    delete inven;
}

void UIScene::Update()
{
    for (Button* button : buttons)
        button->Update();

    store->Update();
    inven->Update();
}

void UIScene::Render()
{
    for (Button* button : buttons)
        button->Render();

    store->Render();
    inven->Render();
}

void UIScene::PostRender()
{
    ImGui::Text(str.c_str());

    //FONT->RenderText("HelloWorld", CENTER);

    store->Edit();

    store->PostRender();
    inven->PostRender();
}

void UIScene::OnClickButton1()
{
    str = "Click Button1";
    //SceneManager::Get()->ChangeScene("Break");

    store->SetActive(!store->IsActive());
}

void UIScene::OnClickButton2()
{
    str = "Click Button2";
    //SceneManager::Get()->ChangeScene("Acade");
    inven->SetActive(!inven->IsActive());
}

#pragma once

class UIScene : public Scene
{
public:
    UIScene();
    ~UIScene();

    void Update() override;
    void Render() override;
    void PostRender() override;

    void OnClickButton1();
    void OnClickButton2();

private:
    vector<Button*> buttons;

    string str = "None";

    Store* store;
    Inventory* inven;
};
#include "Framework.h"
#include "SampleScene.h"
#include "rapidjson/document.h"
using namespace rapidjson;

SampleScene::SampleScene()
{
    SampleStageColData data;
    data = LoadFromJSON(L"DataTables/Json/sampleColData.json");

    back = new ImageObject(L"Textures/Acade/sampleBack.png");
    back->SetPos(Vector2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2));
    back->Update();

    colCount = data.colCount;
    allCols = new ImageObject * [colCount];
    for (size_t i = 0; i < colCount; i++)
    {
        wstring path = data.cols[i].path;
        Vector2 start = Vector2(0, 0);
        Vector2 end = Vector2(data.cols[i].Widthcount, data.cols[i].heightCount);
        allCols[i] = new ImageObject(path, start, end);

        allCols[i]->SetPos(data.cols[i].startPos);
    }

    player = new SamplePlayer();

    player->SetLandCollider(colCount, reinterpret_cast<BoxCollider**>(allCols));
}

SampleScene::~SampleScene()
{
    for (size_t i = 0; i < colCount; i++)
    {
        delete allCols[i];
    }
    delete player;
    delete back;

}

void SampleScene::Update()
{
    player->Update();
    //back->Update();
    for (size_t i = 0; i < colCount; i++)
    {
        allCols[i]->Update();
    }
}

void SampleScene::Render()
{
    back->Render();
    player->Render();
    for (size_t i = 0; i < colCount; i++)
    {
        allCols[i]->Render();
    }

}
void SampleScene::PostRender()
{


}


wstring SampleScene::StringToWString(const string& str) {
    return wstring(str.begin(), str.end());
}

SampleStageColData SampleScene::LoadFromJSON(const wstring& filePath)
{
    SampleStageColData data;

    // JSON ���� �б�
    ifstream file(filePath);
    if (!file.is_open()) {

        return data;
    }

    string jsonContent((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    // JSON �Ľ�
    Document document;
    document.Parse(jsonContent.c_str());

    if (document.HasParseError()) {

        return data;
    }

    // ������ �б�
    data.colCount = document["colCount"].GetInt();

    const Value& colsArray = document["cols"];
    for (SizeType i = 0; i < colsArray.Size(); i++) {
        const Value& colObj = colsArray[i];

        SampleStageCol col;
        col.path = StringToWString(colObj["path"].GetString());
        col.startPos.x = colObj["startPos"]["x"].GetInt();
        col.startPos.y = colObj["startPos"]["y"].GetInt();
        col.Widthcount = colObj["Widthcount"].GetInt();
        col.heightCount = colObj["heightCount"].GetInt();

        data.cols.push_back(col);
    }

    return data;
}
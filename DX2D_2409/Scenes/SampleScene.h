#include "Framework.h"

struct SampleStageCol
{
    wstring path;
    Vector2 startPos;
    int Widthcount;
    int heightCount;

};

struct SampleStageColData
{
    int colCount;
    vector<SampleStageCol> cols;

};


class SampleScene : public Scene
{
public:
    SampleScene();
    ~SampleScene();

    void Update() override;
    void Render() override;
    void PostRender() override;

private:
    int colCount;
    ImageObject** allCols;
    SamplePlayer* player;

    ImageObject* back;
    SampleStageCol** cols;

    wstring StringToWString(const string& str);

    SampleStageColData LoadFromJSON(const wstring& filePath);
};


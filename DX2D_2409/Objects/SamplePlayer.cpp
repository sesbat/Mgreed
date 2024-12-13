#include "Framework.h"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h" // GetParseError_En ����� ���� �ʿ�
using namespace rapidjson;
#include "SamplePlayer.h"

SamplePlayer::SamplePlayer()
{
    landCollider = NULL;
    image = new Quad(L"Textures/Acade/mario.png",
    image = new Quad(L"Textures/Sample/mario.png",
        Vector2(6.0f / 8.0f, 3.0f / 4.0f), Vector2(7.0f / 8.0f, 1));
    image->SetParent(this);
    image->GetMaterial()->SetMaxFrame(8, 4);

    UpdateSize(image->GetSize());

    pos = CENTER;
    pos.x += 100;
    UpdateWorld();
}

SamplePlayer::~SamplePlayer()
{
}

void SamplePlayer::Update()
{
    Move();
    Jump();

    RigidbodyObject::Update();

    CheckCollider();

    image->UpdateWorld();
}

void SamplePlayer::Render()
{
    image->Render();
    Collider::Render();
}

void SamplePlayer::Move()
{
    bool isMove = false;

    if (KEY->Press(VK_RIGHT))
    {
        velocity.x += ACCELATION * DELTA;
        isMove = true;
    }
    if (KEY->Press(VK_LEFT))
    {
        velocity.x -= ACCELATION * DELTA;
        isMove = true;
    }
}

void SamplePlayer::Jump()
{
    if (KEY->Down(VK_UP))
    {
        velocity.y = JUMP_POWER;
    }
}

void SamplePlayer::CheckCollider()
{
    if (velocity.y > 0) return;

    for (size_t i = 0; i < colCount; i++)
    {
        Vector2 overlap;
        if (landCollider[i]->IsCollision(this, &overlap))
        {
            velocity.y = 0.0f;
            Translate(Vector2::Up() * overlap.y);
        }
    }
}

void SamplePlayer::LoadFromJSON(const wstring& filePath)
{
    ifstream file(filePath);
    if (!file.is_open()) {
        wcout << L"Failed to open file: " << filePath << endl;
        return;
    }

    string jsonContent((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    // JSON �Ľ�
    Document document;
    document.Parse(jsonContent.c_str());

    if (document.HasParseError()) {
        wcout << L"JSON parsing error: " << GetParseError_En(document.GetParseError())
            << L" (Offset: " << document.GetErrorOffset() << L")" << endl;
        return;
    }

    if (!document.IsArray()) {
        wcout << L"Invalid JSON format: Expected an array of animation frames" << endl;
        return;
    }

    // AnimationFrame ���� �Ҵ�
    int frameCount = document.Size();
    animationInfo = new AnimationFrame[frameCount];

    for (SizeType i = 0; i < document.Size(); i++) {
        const Value& frameObj = document[i];

        // AnimationFrame ������ ä���
        AnimationFrame& frame = animationInfo[i];
        frame.miliSec = frameObj["miliSec"].GetInt();

        const Value& animationInfoObj = frameObj["animationInfo"];
        for (Value::ConstMemberIterator it = animationInfoObj.MemberBegin(); it != animationInfoObj.MemberEnd(); ++it) {
            // ��� ���� ��������
            int outputOrder = stoi(it->name.GetString());

            // ��� ������ �������� ������ �ʱ�ȭ
            if (frame.animationInfo.find(outputOrder) == frame.animationInfo.end()) {
                frame.animationInfo[outputOrder] = map<PlayerPart, PartInfo>();
            }

            const Value& partMap = it->value;
            for (Value::ConstMemberIterator partIt = partMap.MemberBegin(); partIt != partMap.MemberEnd(); ++partIt) {
                // PlayerPart Ÿ�� ��ȯ
                PlayerPart partType = static_cast<PlayerPart>(stoi(partIt->name.GetString()));
                const Value& partInfoObj = partIt->value;

                // PartInfo ������ ä���
                PartInfo partInfo;
                partInfo.rect.x = partInfoObj["rect"]["x"].GetInt();
                partInfo.rect.y = partInfoObj["rect"]["y"].GetInt();
                partInfo.sourceRect.x = partInfoObj["sourceRect"]["x"].GetInt();
                partInfo.sourceRect.y = partInfoObj["sourceRect"]["y"].GetInt();
                partInfo.displayRect.x = partInfoObj["displayRect"]["x"].GetInt();
                partInfo.displayRect.y = partInfoObj["displayRect"]["y"].GetInt();
                partInfo.pathIndex = partInfoObj["pathIndex"].GetInt();

                // �����͸� animationInfo�� �߰�
                frame.animationInfo[outputOrder][partType] = partInfo;
            }
        }
    }

    wcout << L"Successfully loaded animation frames from JSON: " << filePath << endl;
}

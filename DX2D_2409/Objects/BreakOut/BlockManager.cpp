#include "Framework.h"

BlockManager::BlockManager()
{    
}

BlockManager::~BlockManager()
{
    DeleteBlocks();
}

void BlockManager::Render()
{
    for (Block* block : blocks)
        block->Render();
}

void BlockManager::LoadStage(int stageNum)
{
    string fileName = "DataTables/Stage" + to_string(stageNum) + ".csv";

    ifstream loadFile(fileName);

    string line;
    
    int y = 0;

    while (getline(loadFile, line))
    {        
        int x = 0;
        while (true)
        {            
            int findPos = line.find_first_of(",");

            int type = stoi(line.substr(0, findPos));
                        
            if (type)
            {
                Block* block = new Block(type);
                block->SetScale(1.5f, 1.5f);
                block->Update();

                Vector2 start = startPos;
                start.x += block->HalfSize().x;
                start.y -= block->HalfSize().y;
                Vector2 pos = block->Size() * Vector2(x, -y) + start;
                block->SetPos(pos);
                
                block->Update();
                blocks.push_back(block);                
            }
            
            line = line.substr(findPos + 1);
            x++;

            if (findPos == line.npos)
                break;
        } 

        y++;
    }
}

void BlockManager::CollisionBall(Ball* ball)
{
    Vector2 overlap;
    for (Block* block : blocks)
    {
        if (block->GetHp() <= 0) continue;

        if (block->IsCollision(ball, &overlap))
        {
            block->Damage();

            if (overlap.x < overlap.y)//�¿��浹
            {
                if (ball->GetPos().x > block->GetPos().x)
                {
                    ball->Translate(Vector2::Right() * overlap.x);
                }
                else
                {
                    ball->Translate(Vector2::Left() * overlap.x);
                }

                ball->HorizontalCollision();
            }
            else//�����浹
            {
                if (ball->GetPos().y > block->GetPos().y)
                {
                    ball->Translate(Vector2::Up() * overlap.y);
                }
                else
                {
                    ball->Translate(Vector2::Down() * overlap.y);
                }

                ball->VerticalCollision();
            }

            if (CheckClear())
            {
                ball->SetReady();
            }
            return;
        }
    }
}

bool BlockManager::CheckClear()
{
    bool isClear = true;

    for (Block* block : blocks)
    {
        if (block->GetHp() > 0)
        {
            isClear = false;
            break;
        }
    }

    if (isClear)
    {
        if (MessageBox(hWnd, L"Clear", L"Clear", MB_OK))
        {
            NextStage();
        }
    }

    return isClear;
}

void BlockManager::NextStage()
{
    stage++;

    DeleteBlocks();
    LoadStage(stage);
}

void BlockManager::DeleteBlocks()
{
    for (Block* block : blocks)
        delete block;

    blocks.clear();
}

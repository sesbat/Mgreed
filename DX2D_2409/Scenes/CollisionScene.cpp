#include "Framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
    //colliders.push_back(new CircleCollider());
    //colliders.back()->SetPos(CENTER_X, CENTER_Y);
    //colliders.back()->SetTag("Circle1");
    //colliders.push_back(new CircleCollider());
    //colliders.back()->SetPos(CENTER_X, CENTER_Y);
    //colliders.back()->SetTag("Circle2");
    //colliders.push_back(new BoxCollider());
    //colliders.back()->SetPos(CENTER_X, CENTER_Y);
    //colliders.back()->SetTag("Box1");
    //colliders.push_back(new BoxCollider());
    //colliders.back()->SetPos(CENTER_X, CENTER_Y);
    //colliders.back()->SetTag("Box2");

    colliders.push_back(new LineCollider(Vector2(0, 0), Vector2(100, 0)));
    colliders.back()->SetPos(CENTER_X, CENTER_Y);
    colliders.back()->SetTag("Line1");
    //colliders.push_back(new LineCollider(Vector2(0, 0), Vector2(0, 100)));
    //colliders.back()->SetPos(CENTER_X, CENTER_Y);
    //colliders.back()->SetTag("Line2");
    //colliders.push_back(new BoxCollider());
    //colliders.back()->SetPos(CENTER_X, CENTER_Y);
    //colliders.back()->SetTag("Box1");
    colliders.push_back(new CircleCollider());
    colliders.back()->SetPos(CENTER_X, CENTER_Y);
    colliders.back()->SetTag("Circle2");
    colliders.push_back(new CircleCollider(5));
    colliders.back()->SetPos(CENTER_X, CENTER_Y);
    colliders.back()->SetTag("Circle1");
}

CollisionScene::~CollisionScene()
{
    for (Collider* collider : colliders)
        delete collider;
}

void CollisionScene::Update()
{
    Vector2 overlap;
        
    //if (colliders[0]->IsPointCollision(mousePos))
    if (colliders[0]->IsCollision(colliders[1], &overlap))    
    {
        colliders[0]->GetMaterial()->SetColor(1, 0, 0);

        colliders[2]->SetPos(overlap);

        //if (GetAsyncKeyState(VK_LBUTTON))
        //{
        //    MessageBox(hWnd, L"GameOver", L"GameOver", MB_OK);
        //    DestroyWindow(hWnd);
        //}
    }
    else
    {
        colliders[0]->GetMaterial()->SetColor(0, 1, 0);
    }

    for (Collider* collider : colliders)
        collider->UpdateWorld();
}

void CollisionScene::Render()
{
    for (Collider* collider : colliders)
        collider->Render();
}

void CollisionScene::PostRender()
{
    for (Collider* collider : colliders)
        collider->Edit();
}

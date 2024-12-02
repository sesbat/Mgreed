#pragma once

//임시
class CollisionManager :public Singleton<CollisionManager>
{
public:
    void AddCollider(Collider* collider);
    void RemoveCollider(Collider* collider);
    void CheckCollisions();

private:
    vector<Collider*> colliders;
};

void CollisionManager::AddCollider(Collider* collider)
{
    colliders.push_back(collider);
}

void CollisionManager::RemoveCollider(Collider* collider) 
{
    colliders.erase(remove(colliders.begin(), colliders.end(), collider), colliders.end());
}

void CollisionManager::CheckCollisions() 
{
    for (size_t i = 0; i < colliders.size(); ++i) 
    {
        for (size_t j = i + 1; j < colliders.size(); ++j) 
        {
            /*if (colliders[i]->Intersects(colliders[j])) 
            {
            }*/
        }
    }
}
#include "ObjectManager.h"
#include "URenderer.h"

#include <ranges>


void ObjectManager::Initialize(URenderer* renderer)
{
    Renderer = renderer;
}

void ObjectManager::Update(float DeltaTime , ID3D11Buffer* pBuffer , UINT numVertices)
{
    ProcessMove(DeltaTime);
    ProcessCheckCollision();
    ProcessRender(pBuffer , numVertices);

    ProcessDestroy();
}

void ObjectManager::FixedUpdate(float FixedTime)
{
}

void ObjectManager::RegistObject(CircleObject* InCircleObject)
{
    if (!ObjectsMap.contains(InCircleObject->GetWorld()))
    {
        ObjectsMap.insert({InCircleObject->GetWorld() , std::vector<CircleObject*>()});
    }

    ObjectsMap.at(InCircleObject->GetWorld()).push_back(InCircleObject);
}

void ObjectManager::Destroy(CircleObject* InCircleObject)
{
    DestroyList.emplace_back(InCircleObject);
    auto vector = ObjectsMap.at(InCircleObject->GetWorld());
    const auto it = std::ranges::find(vector , InCircleObject);
    ObjectsMap.at(InCircleObject->GetWorld()).erase(it);
}

// 라이프 사이클에 의해 Update 이후에 사용
void ObjectManager::ProcessDestroy()
{
    for (auto destroyObject : DestroyList)
    {
        // 이따가 destroy를 직접 시키는 게 좋을 지 어떻게 하는게 좋을지 물어보자.
        destroyObject->OnDestroy();
    }
    DestroyList.clear();
}

void ObjectManager::ProcessMove(float DeltaTime)
{
    for (const auto& Objects : ObjectsMap | std::views::values) // Value만 갸져오기
    {
        for (CircleObject* Object : Objects)
        {
            Object->Move(DeltaTime);
        }
    }
}

void ObjectManager::ProcessCheckCollision()
{
    for (auto Objects : ObjectsMap | std::views::values)
    {
        for (int i = 0; i < Objects.size(); ++i)
        {
            for (int j = i + 1; j < Objects.size(); ++j)
            {
                CircleObject& objectA = *Objects[i];
                CircleObject& objectB = *Objects[j];

                if (CheckCollision(objectA , objectB))
                {
                    objectA.HandleBallCollision(objectB);
                }
            }
        }
    }
}

void ObjectManager::ProcessRender(ID3D11Buffer* pBuffer , UINT numVertices) const
{
    for (const auto& [WorldEnum, Objects] : ObjectsMap)
    {
        Renderer->PrepareViewport(WorldEnum);
        for (const CircleObject* vector : Objects)
        {
            vector->Render(*Renderer);
            Renderer->RenderPrimitive(pBuffer , numVertices);
        }
    }
}


bool ObjectManager::CheckCollision(const CircleObject& A , const CircleObject& B) const
{
    const float Distance = (A.GetLocation() - B.GetLocation()).Length();
    return Distance <= (A.GetRadius() + B.GetRadius());
}

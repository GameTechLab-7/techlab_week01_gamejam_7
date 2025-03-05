#include <ranges>
#include "ObjectManager.h"

#include "URenderer.h"
#include "GameManager.h"
#include "Constant.h"

void ObjectManager::Initialize(URenderer* renderer)
{
	Renderer = renderer;
}

void ObjectManager::Update(float DeltaTime)
{
	ProcessUpdate(DeltaTime);

	ProcessMove(DeltaTime);
	ProcessCheckCollision();
	ProcessRender();

	ProcessDestroy();
}

void ObjectManager::FixedUpdate(float FixedTime)
{
	ProcessFixedUpdate(FixedTime);
}

void ObjectManager::Destroy(CircleObject* InCircleObject)
{
    // pending queue에 추가, 삭제는 나중에 Process Destroy에서
    DestroyQueue.push(InCircleObject->shared_from_this());
}

void ObjectManager::DestroyAll()
{
    for (const auto& Objects : ObjectsMap | std::views::values)
    {
        for (const auto& Object : Objects)
        {
            DestroyQueue.push(Object);
        }
    }
}

// 라이프 사이클에 의해 Update 이후에 사용
void ObjectManager::ProcessDestroy()
{
    while (!DestroyQueue.empty())
    {
        if (const auto& Object = DestroyQueue.front().lock())
        {
            Object->OnDestroy();
            ObjectsMap[Object->GetWorld()].erase(Object->shared_from_this());
        }
        DestroyQueue.pop();
    }
}

void ObjectManager::ProcessUpdate(float DeltaTime)
{
    for (const auto& Objects : ObjectsMap | std::views::values)
    {
        for (const auto& Object : Objects)
        {
            Object->Update(DeltaTime);
        }
    }
}


void ObjectManager::ProcessFixedUpdate(float FixedTime)
{
    for (const auto& Objects : ObjectsMap | std::views::values)
    {
        for (const auto& Object : Objects)
        {
            Object->FixedUpdate(FixedTime);
        }
    }
}

void ObjectManager::ProcessMove(float DeltaTime)
{
    for (const auto& Objects : ObjectsMap | std::views::values) // Value만 갸져오기
    {
        for (const auto& Object : Objects)
        {
            Object->Move(DeltaTime);
        }
    }
}

void ObjectManager::ProcessCheckCollision()
{
    for (auto Objects : ObjectsMap | std::views::values)
    {
        for (auto Object : Objects)
        {
            Object->SetCollisionFlag(false);
        }
    }

    for (auto Objects : ObjectsMap | std::views::values)
    {
        std::vector<std::shared_ptr<CircleObject>> ObjVec = { Objects.begin(), Objects.end() };
        for (size_t i = 0; i < Objects.size(); ++i)
        {
            CircleObject& objectA = *ObjVec[ i ];
            FVector3 normal;
            if (CheckWallCollision(objectA , normal))
            {
                objectA.HandleWallCollision(normal);
            }
        }
    }


	for (auto Objects : ObjectsMap | std::views::values)
	{
	    std::vector<std::shared_ptr<CircleObject>> ObjVec = {Objects.begin(), Objects.end()};
		for (size_t i = 0; i < Objects.size(); ++i)
		{
			for (size_t j = i + 1; j < Objects.size(); ++j)
			{
				CircleObject& objectA = *ObjVec[ i ];
				CircleObject& objectB = *ObjVec[ j ];

				if (CheckCollision(objectA , objectB))
				{
					ObjVec[i]->HandleBallCollision(ObjVec[j].get());
                    ObjVec[j]->HandleBallCollision(ObjVec[i].get());

                    ObjVec[i]->SetCollisionFlag(true);
					ObjVec[j]->SetCollisionFlag(true);
				}
			}

		}
	}
}

void ObjectManager::ProcessRender() const
{
    const URenderer* pRenderer = GameManager::GetInstance().GetRenderer();
    if (pRenderer == nullptr)
    {
        return;
    }

    for (const auto& [WorldEnum, Objects] : ObjectsMap)
    {
        pRenderer->PrepareViewport(WorldEnum);
        for (const auto& Object : Objects)
        {
            Object->Render(*pRenderer);
        }
    }
}


bool ObjectManager::CheckCollision(const CircleObject& A , const CircleObject& B) const
{
	if (A.IsCollisionProcessing() || B.IsCollisionProcessing())
	{
		return false;
	}
	const float Distance = ( A.GetLocation() - B.GetLocation() ).Length();
	return Distance <= ( A.GetRadius() + B.GetRadius() );
}

bool ObjectManager::CheckWallCollision(const CircleObject& object, FVector3& normal) const {
    FVector3 Location = object.GetLocation();
    EWorld MyWorld = object.GetWorld();
    float Radius = object.GetRadius();
    normal = FVector3();

    if (Location.x - Radius < WorldWalls[ MyWorld ][ Left ])
    {
        // left
        normal += FVector3(1 , 0 , 0);
    }
    else if (Location.x + Radius > WorldWalls[ MyWorld ][ Right ])
    {
        // right
        normal += FVector3(-1 , 0 , 0);
    }

    if (Location.y + Radius > WorldWalls[ MyWorld ][ Top ])
    {
        // top
        normal += FVector3(0 , -1 , 0);
    }
    else if (Location.y - Radius < WorldWalls[ MyWorld ][ Bottom ])
    {
        // botom
        normal += FVector3(0, 1 , 0);
    }
    normal = normal.Normalize();

    if (normal.Length() < 0.001f) {
        return false;
    }

    return true;
}
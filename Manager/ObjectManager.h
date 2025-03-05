#pragma once
#include <concepts>
#include <memory>
#include <queue>
#include <unordered_set>
#include <unordered_map>

#include "GameObject/CircleObject.h"
#include "AbstractClass/Singleton.h"


class ObjectManager : public Singleton<ObjectManager>
{
public:
	ObjectManager() = default;
	// Update, FixedUpdate
	URenderer* Renderer;

	void Initialize(URenderer* renderer);

	//void Render(World world);
	void Update(float DeltaTime);
	void FixedUpdate(float FixedTime);

	// 일회성
	template<typename Obj>
		requires std::derived_from<Obj , CircleObject>
	Obj* RegistObject(EWorld eWorld);

	void Destroy(CircleObject* InCircleObject);
	void DestroyAll();

protected:
	std::unordered_map<EWorld , std::unordered_set<std::shared_ptr<CircleObject>>> ObjectsMap;
	std::queue<std::weak_ptr<CircleObject>> DestroyQueue;

private:
	// 라이프 사이클에 의해 Update 이후에 사용
	void ProcessDestroy();

	void ProcessUpdate(float DeltaTime);
	void ProcessFixedUpdate(float FixedTime);

	void ProcessMove(float DeltaTime);		// velocity에 따른 움직임.

	void ProcessCheckCollision();

	void ProcessRender() const;

	bool CheckCollision(const CircleObject& A , const CircleObject& B) const;
	bool CheckWallCollision(const CircleObject& object, FVector3& normal) const;
};

template <typename Obj>
	requires std::derived_from<Obj, CircleObject>
Obj* ObjectManager::RegistObject(EWorld eWorld)
{
	const auto object = std::make_shared<Obj>(eWorld);
	if (!ObjectsMap.contains(eWorld))
	{
		ObjectsMap.insert({ eWorld, {} });
	}

	ObjectsMap[ eWorld ].insert(object);
	return object.get();
}
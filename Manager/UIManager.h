#pragma once
#include "AbstractClass/Singleton.h"
#include "URenderer.h"
#include "UIObject/UIObject.h"
#include "enum.h"

#include <vector>
#include <unordered_map>
#include <queue>

class UIManager : public Singleton<UIManager> {
public:

	URenderer* Renderer;

	void Initialize(URenderer* renderer);

	void Update(float DeltaTime);

	UIObject* CreateUIObject(FVector3 Location, FVector3 Scale, const char* TexturePath, void(*OnClickMethod)() = nullptr);

	template<typename Obj>
		requires std::derived_from<Obj , UIObject>
	Obj* RegistUIObject(EScene scene);

protected:
	std::unordered_map<int, std::vector<std::shared_ptr<UIObject>>> UIObjectsMap;
	std::queue<std::weak_ptr<UIObject>> DestroyQueue;

private:

	void ProcessUpdate(float DeltaTime);
	
	void ProcessRender() const;

	bool CheckMouseInBound(FVector3 mouseVec, FVector3 RectLocation, FVector3 Scale);
	  
};

template <typename Obj>
	requires std::derived_from<Obj , UIObject>
Obj* UIManager::RegistUIObject(EScene scene)
{
	const auto object = std::make_shared<Obj>(scene);
	if (!UIObjectsMap.contains(scene))
	{
		UIObjectsMap.insert({ scene, {} });
	}

	UIObjectsMap[ scene ].push_back(object);
	return object.get();
}
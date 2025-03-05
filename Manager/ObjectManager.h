#pragma once
#include <d3d11.h>
#include <vector>
#include <memory>
#include <unordered_map>

#include "GameObject/CircleObject.h"
#include "AbstractClass/Singleton.h"
#include "GameObject/Player.h"

class ObjectManager : public Singleton<ObjectManager>
{
public:
	ObjectManager();
	// Update, FixedUpdate
	URenderer* Renderer;

	void Initialize(URenderer* renderer);

	//void Render(World world);
	void Update(float DeltaTime, ID3D11Buffer* pBuffer , UINT numVertices);
	void FixedUpdate(float FixedTime);
	// 일회성
	template<typename T> 
		requires std::is_base_of<CircleObject , T>::value
	T* RegistObject(EWorld eWorld) {
		T* object = new T(eWorld);

		if (!ObjectsMap.contains(eWorld))
		{
			ObjectsMap.insert({ eWorld , std::vector<CircleObject*>() });
		}

		ObjectsMap.at(eWorld).push_back(object);

		return object;
	}

	void Destroy(CircleObject* InCircleObject);

protected:
	std::unordered_map<EWorld , std::vector<CircleObject*>> ObjectsMap;
	std::vector <std::shared_ptr<CircleObject>> DestroyList;

private:

	// 라이프 사이클에 의해 Update 이후에 사용
	void ProcessDestroy();

	void ProcessUpdate(float DeltaTime);
	void ProcessFixedUpdate(float FixedTime);
	
	void ProcessMove(float DeltaTime);		// velocity에 따른 움직임.

	void ProcessCheckCollision();

	void ProcessRender(ID3D11Buffer* pBuffer , UINT numVertices) const;

	bool CheckCollision(const CircleObject& A , const CircleObject& B) const;
};

//template<typename T> //requires std::is_base_of<CircleObject , T>::value
//T* ObjectManager::RegistObject(EWorld eWorld)
//{
//	/*T* object = new T(eWorld);
//
//	if (!ObjectsMap.contains(eWorld))
//	{
//		ObjectsMap.insert({ eWorld , std::vector<CircleObject*>() });
//	}
//
//	ObjectsMap.at(eWorld).push_back(object);*/
//
//	return nullptr;
//}

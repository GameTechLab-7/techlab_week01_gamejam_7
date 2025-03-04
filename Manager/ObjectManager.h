#pragma once
#include <d3d11.h>
#include <vector>
#include <memory>
#include <unordered_map>

#include "GameObject/CircleObject.h"
#include "AbstractClass/Singleton.h"


class ObjectManager : Singleton<ObjectManager>
{
public:
	// Update, FixedUpdate
	URenderer* Renderer;

	void Initialize(URenderer* renderer);

	// 라이프사이클
	//void Render(World world);
	void Update(float DeltaTime, ID3D11Buffer* pBuffer , UINT numVertices);
	void FixedUpdate(float FixedTime);

	// 일회성
	void RegistObject(CircleObject* InCircleObject);
	void Destroy(CircleObject* InCircleObject);

protected:
	std::unordered_map<EWorld , std::vector<CircleObject*>> ObjectsMap;
	std::vector <std::shared_ptr<CircleObject>> DestroyList;

private:

	// 라이프 사이클에 의해 Update 이후에 사용
	void ProcessDestroy();

	void ProcessMove(float DeltaTime);		// velocity에 따른 움직임.

	void ProcessCheckCollision();

	void ProcessRender(ID3D11Buffer* pBuffer , UINT numVertices) const;

	bool CheckCollision(const CircleObject& A , const CircleObject& B) const;
};
#pragma once

#include "CircleObject.h"
#include "Singleton.h"
#include <vector>
#include <map>
#include <memory>

class ObjectManager : Singleton< ObjectManager> {
public:
	
	// Update, FixedUpdate
	URenderer* uRenderer;

	void Inititalize(URenderer* renderer);

	// 라이프사이클
	//void Render(World world);
	void Update(float DeltaTime, ID3D11Buffer* pBuffer , UINT numVertices);
	void FixedUpdate(float FixedTime);

	// 일회성
	void RegistObject(CircleObject* CircleObject);
	void Destory(CircleObject* CircleObject);

protected:
	std::map<EWorld , std::vector<CircleObject*>> objectsMap;
	std::vector <std::shared_ptr<CircleObject>> destroyList;

private:

	// 라이프 사이클에 의해 Update 이후에 사용
	void ProcessDestroy();

	void ProcessMove(const float tick);		// velocity에 따른 움직임.

	void ProcessCheckCollision();

	void ProcessRender(ID3D11Buffer* pBuffer , UINT numVertices);

	bool CheckCollision(const CircleObject& A , const CircleObject& B);
};
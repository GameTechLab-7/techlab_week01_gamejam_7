#pragma once

#include "CircleObject.h"
#include "Singleton.h"
#include <vector>
#include <map>
#include <memory>

class ObjectManager : public Singleton<ObjectManager> {
public:
	
	// Update, FixedUpdate
	std::map<EWorld, std::vector<CircleObject*>> objectsMap;
	std::vector <std::shared_ptr<CircleObject>> destroyList;

	// !NOTE : 렌더러는 게임매니저를 통해서만 접근
	//URenderer* URenderer;


	// 라이프사이클
	//void Render(World world);
	void Update(float DeltaTime);
	void FixedUpdate(float FixedTime);

	// 일회성
	void RegistObject(CircleObject* CircleObject, EWorld world);
	void Destory(CircleObject* CircleObject);

private:

	// 라이프 사이클에 의해 Update 이후에 사용
	void ProcessDestroy();

	void ProcessMove(const float tick);		// velocity에 따른 움직임.

	void ProcessCheckCollision();

	void ProcessRender();

	bool CheckCollision(const CircleObject& A , const CircleObject& B);
};
#pragma once

#include "CircleObject.h"
#include "Singleton.h"
#include <vector>
#include <map>

class ObjectManager : Singleton< ObjectManager> {
public:

	// Update, FixedUpdate
	std::map<World, std::vector<CircleObject*>> objectsMap;
	std::vector<CircleObject*> destroyList;
	URenderer* URenderer;


	// 라이프사이클
	void Render(World world);
	void Update(float DeltaTime);
	void FixedUpdate(float FixedTime);

	// 일회성
	void RegistObject(CircleObject* CircleObject, World world);
	void Destory(CircleObject* CircleObject);

private:

	// 라이프 사이클에 의해 Update 이후에 사용
	void ProcessDestroy();

	void ProcessMove(const float tick);		// velocity에 따른 움직임.

	void ProcessCheckCollision();

	void ProcessRender();

	bool CheckCollision(const CircleObject& A , const CircleObject& B);
};
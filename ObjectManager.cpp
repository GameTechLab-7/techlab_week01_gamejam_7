#include "ObjectManager.h"


void ObjectManager::Update(float DeltaTime) {
		ProcessMove(DeltaTime);
		ProcessCheckCollision();
		ProcessRender();

		ProcessDestroy();
	}

	void ObjectManager::FixedUpdate(float FixedTime) {

	}

	void ObjectManager::RegistObject(CircleObject* circleObject , EWorld world) {
		if (objectsMap.find(world) == objectsMap.end()) {
			objectsMap.insert({ world, std::vector<CircleObject*>()});
		}
		else {
			objectsMap.at(world).push_back(circleObject);
		}
	}

	void ObjectManager::Destory(CircleObject* CircleObject) {
		destroyList.emplace_back( CircleObject );
		auto vector = objectsMap.at(CircleObject->MyWorld);
		auto it = std::find(vector.begin() , vector.end() , CircleObject);
		objectsMap.at(CircleObject->MyWorld).erase(it);
	}

	// 라이프 사이클에 의해 Update 이후에 사용
	void ObjectManager::ProcessDestroy() {
		for (auto destroyObject : destroyList)
		{
			// 이따가 destroy를 직접 시키는 게 좋을 지 어떻게 하는게 좋을지 물어보자.
			destroyObject->OnDestroy();
		}
		destroyList.clear();
	}

	void ObjectManager::ProcessMove(const float tick) {
		for (auto vectors : objectsMap) {
			for (auto vector : vectors.second) {
				vector->Move(tick);
			}
		}
	}

	void ObjectManager::ProcessCheckCollision() {
		for (auto objectPair : objectsMap) {
			auto objects = objectPair.second;
			for (int i = 0; i < objects.size(); ++i)
			{
				for (int j = i + 1; j < objects.size(); ++j)
				{
					CircleObject& objectA = *objects[ i ];
					CircleObject& objectB = *objects[ j ];

					if (CheckCollision(objectA , objectB))
					{
						objectA.HandleBallCollision(objectB);
					}
				}
			}
		}
	}

	void ObjectManager::ProcessRender() {
		for (auto vectors : objectsMap) {
			URenderer->PrepareViewport(vectors.first);
			for (auto vector : vectors.second) {
				vector->Render(*URenderer);
			}
		}
	}


	bool ObjectManager::CheckCollision(const CircleObject& A , const CircleObject& B)
	{
		const float Distance = ( A.Location - B.Location ).Length();
		return Distance <= ( A.Radius + B.Radius );
	}
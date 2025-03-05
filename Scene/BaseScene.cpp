#include "BaseScene.h"
#include "Manager/ObjectManager.h"


void BaseScene::Update(float DeltaTime)
{
	// !TODO : 프레임 표시, etc..
	ObjectManager::GetInstance().Update(DeltaTime);
}

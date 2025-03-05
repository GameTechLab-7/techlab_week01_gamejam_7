#include "MainGameScene.h"
#include "GameObject/Player.h"
#include "Manager/ObjectManager.h"
#include "Manager/GameManager.h"


void MainGameScene::LoadScene()
{
	// !TODO : 플레이어 두 개 받아와서 캐시
	// ObjectManager->GetPlayer()
	// ObjectManager->GetEnemy()
	// !TODO : 

	leftPlayer = ObjectManager::GetInstance().RegistObject<Player>(First);
	rightPlayer = ObjectManager::GetInstance().RegistObject<Player>(Second);
}

void MainGameScene::ExitScene()
{
	// !TODO : object 매니저 클리어 호출
	// ObjectManager->Destroy(left)

	ObjectManager::GetInstance().Destroy(leftPlayer);
	ObjectManager::GetInstance().Destroy(rightPlayer);
}

void MainGameScene::Update(float DeltaTime)
{
	BaseScene::Update(DeltaTime);
	ObjectManager::GetInstance().Update(DeltaTime);
}

void MainGameScene::Render()
{
}

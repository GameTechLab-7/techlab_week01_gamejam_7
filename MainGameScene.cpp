#include "MainGameScene.h"
#include "Player.h"
#include "ObjectManager.h"
#include "GameManager.h"

void MainGameScene::LoadScene()
{
	// !TODO : 플레이어 두 개 받아와서 캐시
	// ObjectManager->GetPlayer()
	// ObjectManager->GetEnemy()
	// !TODO : 

	leftPlayer = std::make_shared<Player>(EWorld::first);
	rightPlayer = std::make_shared<Player>(EWorld::second);


	ObjectManager::GetInstance().RegistObject(leftPlayer.get() , EWorld::first);
	ObjectManager::GetInstance().RegistObject(rightPlayer.get() , EWorld::second);
}

void MainGameScene::ExitScene()
{
	// !TODO : object 매니저 클리어 호출
	// ObjectManager->Destroy(left)

	ObjectManager::GetInstance().Destory(leftPlayer.get());
	ObjectManager::GetInstance().Destory(rightPlayer.get());
}

void MainGameScene::Update(float deltaTime)
{
	BaseScene::Update(deltaTime);
	ObjectManager::GetInstance().Update(deltaTime);
}

void MainGameScene::Render()
{
}

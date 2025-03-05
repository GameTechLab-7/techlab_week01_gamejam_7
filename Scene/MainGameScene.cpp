#include "MainGameScene.h"
#include "GameObject/Player.h"
#include "Manager/ObjectManager.h"
#include "Manager/GameManager.h"
#include "InputSystem.h"

void MainGameScene::LoadScene()
{
	// !TODO : 플레이어 두 개 받아와서 캐시
	// ObjectManager->GetPlayer()
	// ObjectManager->GetEnemy()
	// !TODO : 
	InputHandlerInstance = std::make_unique<InputHandler>();

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
	RenderWall(GameManager::GetInstance().GetRenderer());
}

FVertexSimple LineVertices[ ] = {
	{1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
	{1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
};

void MainGameScene::RenderWall(URenderer* Renderer) {

	ID3D11Buffer* VertexBufferLine = Renderer->CreateVertexBuffer(LineVertices , sizeof(LineVertices));
	int NumOfLineVertices = ARRAYSIZE(LineVertices);

	Renderer->PrepareViewport(EWorld::First);
	Renderer->UpdateConstant(FVector3() , 1.0f , 0.0f);
	Renderer->PrepareLine();
	Renderer->RenderPrimitive(VertexBufferLine , NumOfLineVertices);
}
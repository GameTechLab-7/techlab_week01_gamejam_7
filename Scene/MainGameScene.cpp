#include "MainGameScene.h"

#include "Manager/GameManager.h"
#include "GameObject/Player.h"
#include "MonsterSpawner.h"
#include "Weapon/WeaponA.h"
#include "Weapon/WeaponB.h"
#include "InputSystem.h"

void MainGameScene::LoadScene()
{

	InputHandlerInstance = std::make_unique<InputHandler>();
  
	LeftPlayer = ObjectManager::GetInstance().RegistObject<Player>(First);
	InitPlayer(LeftPlayer);
	
	RightPlayer = ObjectManager::GetInstance().RegistObject<Player>(Second);
	InitPlayer(RightPlayer);

	SpawnerInfo Info;

	Info.MonsterSpeed = 1.f;
	Info.MonsterScale = 1.f;
	Info.DefaultMonsterNum = 5;
	Info.SpawnRate = 10.0f;
	Info.MonsterIncreaseTime = 5.0f;
	Info.MonsterIncreaseNum = 1;

	Spawner = std::make_unique<MonsterSpawner>(Info);
}

void MainGameScene::ExitScene()
{
	ObjectManager::GetInstance().Destroy(LeftPlayer);
	ObjectManager::GetInstance().Destroy(RightPlayer);

	Spawner.reset();
}

void MainGameScene::Update(float DeltaTime)
{
	InputHandlerInstance->InputUpdate();
	Spawner->Update(DeltaTime);
	BaseScene::Update(DeltaTime);
}

void MainGameScene::Render()
{
	RenderWall(GameManager::GetInstance().GetRenderer());

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Main Game Scene");

    ImGui::Text("Score  Left: %d, Right: %d" , GameManager::GetInstance().GetLogic()->GetScore(EWorld::First) , GameManager::GetInstance().GetLogic()->GetScore(EWorld::Second));

	ImGui::Text("Exp  Left: %d, Right: %d", GameManager::GetInstance().GetLogic()->GetExp(EWorld::First), GameManager::GetInstance().GetLogic()->GetExp(EWorld::Second));

    if (GameManager::GetInstance().GetLogic()->CanUseSpecialSkill(EWorld::First))
    {
        ImGui::Text("Player 1 Can Use Special Skill! Press E!");
    }

	if (GameManager::GetInstance().GetLogic()->CanUseSpecialSkill(EWorld::Second))
	{
        ImGui::Text("Player 2 Can Use Special Skill! Press U!");
	}

#ifdef _DEBUG

    if (ImGui::Button("Left use 10 Score")) {
        GameManager::GetInstance().GetLogic()->SpawnMonsterToWorld(EWorld::Second , 100);
        GameManager::GetInstance().GetLogic()->AddScore(EWorld::First , -10);
    }

    if (ImGui::Button("Right use 10 Score")) {
        GameManager::GetInstance().GetLogic()->SpawnMonsterToWorld(EWorld::First , 100);
        GameManager::GetInstance().GetLogic()->AddScore(EWorld::Second , -10);
    }

    ImGui::Text("Right (Second)");
    auto* rightPlayer = GetPlayer(EWorld::Second);
    if (rightPlayer != nullptr) {
        BaseWeapon* baseWeapon = rightPlayer->GetWeapon();
        int level = GameManager::GetInstance().GetLogic()->GetLv(rightPlayer->GetWorld());
        if (baseWeapon != nullptr) {
            WeaponB* weaponB = dynamic_cast< WeaponB* >( baseWeapon );
            if (weaponB != nullptr) {
                if (ImGui::SliderFloat("speed" , &weaponB->WeaponData.AngularSpeed , 0.3 , 2)) {
                }

                if (ImGui::SliderFloat("bullet radius" , &weaponB->WeaponData.BulletRadius , 0.04 , 0.15)) {
                    // Radius에 맞게 변환
                    weaponB->UpdateRadius();
                }

                if (ImGui::SliderFloat("total radius" , &weaponB->WeaponData.TotalRadius , 0.03 , 0.5)) {

                }
                if (ImGui::SliderInt("NumOfBullets" , &weaponB->WeaponData.NumOfBullets , 1 , 10)) {
                    // 개수에 맞게 소환
                    weaponB->Clear();
                    weaponB->SpawnBullet(weaponB->WeaponData.NumOfBullets);
                }

                if (ImGui::SliderFloat("Force" , &weaponB->WeaponData.Force , 1 , 100)) {

                    // 개수에 맞게 소환
                    weaponB->UpdateForce();
                }

                if (ImGui::SliderInt("Level" , &level , 1 , 10)) {

                    // 개수에 맞게 소환
                    GameManager::GetInstance().GetLogic()->SetLevel(rightPlayer->GetWorld() , level);
                }
            }
        }
    }



    ImGui::Text("Left (First)");
    auto* leftPlayer = GetPlayer(EWorld::First);
    if (leftPlayer != nullptr) {
        BaseWeapon* baseWeapon = leftPlayer->GetWeapon();
        int level = GameManager::GetInstance().GetLogic()->GetLv(leftPlayer->GetWorld());
        if (baseWeapon != nullptr) {
            WeaponA* weaponA = dynamic_cast< WeaponA* >( baseWeapon );
            if (weaponA != nullptr) {
                if (ImGui::SliderFloat("A speed" , &weaponA->WeaponData.BulletSpeed , 0.3 , 2)) {
                }

                if (ImGui::SliderFloat("A bullet radius" , &weaponA->WeaponData.BulletSize , 0.04 , 0.15)) {
                }

                if (ImGui::SliderFloat("A Cooldown" , &weaponA->WeaponData.ShootCooldown , 0.03 , 1)) {
                }

                if (ImGui::SliderFloat("A Force" , &weaponA->WeaponData.Force , 1 , 100)) {

                }

                if (ImGui::SliderInt("A Level" , &level , 1 , 10)) {

                    GameManager::GetInstance().GetLogic()->SetLevel(leftPlayer->GetWorld() , level);
                }
            }
        }
    }

    auto* spawner = GetSpawner();
    ImGui::Text("Monster");
    float MonsterSpeed = spawner->GetMonsterSpeed();
    if (ImGui::SliderFloat("Monster Speed" , &MonsterSpeed , 1 , 5)) {
        spawner->SetMonsterSpeed(MonsterSpeed);
    }

    float MonsterScale = spawner->GetMonsterScale();
    if (ImGui::SliderFloat("Monster Scale" , &MonsterScale , 0.5 , 2)) {
        spawner->SetMonsterScale(MonsterScale);
    }

    float DefaultMonsterNum = spawner->GetDefaultMonsterNum();
    if (ImGui::SliderFloat("Default Monster Num" , &DefaultMonsterNum , 3 , 10)) {
        spawner->SetDefaultMonsterNum(DefaultMonsterNum);
    }

    float SpawnRate = spawner->GetSpawnRate();
    if (ImGui::SliderFloat("Monster Spawn Rate" , &SpawnRate , 1 , 7)) {
        spawner->SetSpawnRate(SpawnRate);
    }

    float MonsterIncreaseTime = spawner->GetMonsterIncreaseTime();
    if (ImGui::SliderFloat("Monster Increase Time" , &MonsterIncreaseTime , 2 , 10)) {
        spawner->SetMonsterIncreaseTime(MonsterIncreaseTime);
    }

    int MonsterIncreaseNum = spawner->GetMonsterIncreaseNum();
    if (ImGui::SliderInt("Monster Increase Num" , &MonsterIncreaseNum , 1 , 10)) {
        spawner->SetMonsterIncreaseNum(MonsterIncreaseNum);
    }
#endif // DEBUG

    ImGui::End();
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}


Player* MainGameScene::GetPlayer(EWorld WorldType) const
{
	if (WorldType == EWorld::First)
	{
		return LeftPlayer;
	}
	else
	{
		return RightPlayer;
	}
}


FVertexSimple LineVertices[ ] = {
	{1.0f, -1.0f, 0.0f, 1.0f, -1.0f},
	{1.0f, 1.0f, 0.0f, 1.0f, 1.0f},
};

void MainGameScene::RenderWall(URenderer* Renderer) {

	ID3D11Buffer* VertexBufferLine = Renderer->CreateVertexBuffer(LineVertices , sizeof(LineVertices));
	int NumOfLineVertices = ARRAYSIZE(LineVertices);

	Renderer->PrepareViewport(EWorld::First);
	Renderer->UpdateConstant(FVector3() , 1.0f , 0.0f);
	Renderer->PrepareLine();
	Renderer->RenderPrimitive(VertexBufferLine , NumOfLineVertices);
}

void MainGameScene::InitPlayer(Player* player)
{
	EWorld world = player->GetWorld();
	
	// 프리셋 0, 1에 따라서 플레이어의 무기를 설정
	if (GameManager::GetInstance().GetLogic()->GetPreset(world) == 0)
	{
		WeaponA* weaponA = new WeaponA(player);
		player->SetWeapon(weaponA);
	}
	else
	{
		WeaponB* weaponB = new WeaponB(player);
		player->SetWeapon(weaponB);
	}
}

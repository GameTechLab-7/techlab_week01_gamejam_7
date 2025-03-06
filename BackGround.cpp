#include "BackGround.h"
#include "Manager/ResourceManager.h"
#include "Texture/UTexture2D.h"
#include "Manager/GameManager.h"
#include "GlobalData.h"

BackGround::BackGround()
	: Texture(ResourceManager::GetInstance().LoadTargaFromFile(TITLE_BACKGROUND_TEXTURE_PATH))
{
	Texture->SetPrimitiveType(EObjectType::UI);
}

void BackGround::Render()
{
	URenderer* renderer = GameManager::GetInstance().GetRenderer();

	BaseScene* crrScene = GameManager::GetInstance().GetCurrentScene();

	switch (crrScene->GetCurrentSceneEnum())
	{
	case Title:
		Texture = ResourceManager::GetInstance().LoadTargaFromFile(TITLE_BACKGROUND_TEXTURE_PATH);
		break;
	case Preset:
		Texture = ResourceManager::GetInstance().LoadTargaFromFile(PRESET_BACKGROUND_TEXTURE_PATH);
		break;
	case MainGame:
		Texture = ResourceManager::GetInstance().LoadTargaFromFile(MAIN_BACKGROUND_TEXTURE_PATH);
		break;
	case Result:
		Texture = ResourceManager::GetInstance().LoadTargaFromFile(RESULT_BACKGROUND_TEXTURE_PATH);
		break;
	}


	if (renderer != nullptr && Texture)
	{
		renderer->UpdateConstant(FVector3(0, 0, 0), 1, 0);
		Texture->Render(*renderer);
	}
}

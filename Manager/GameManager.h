#pragma once
#include <concepts>
#include <memory>

#include "URenderer.h"
#include "Scene/BaseScene.h"
#include "AbstractClass/Singleton.h"


/**
 * 
 */
class GameManager : public Singleton<GameManager>
{
private:

    bool bInitialized = false;
    std::unique_ptr<BaseScene> CurrentScene;
    URenderer* Renderer;

public:
    template <typename Scene>
        requires std::derived_from<Scene, BaseScene>
    void ChangeScene();

    BaseScene* GetCurrentScene() const
    {
        return CurrentScene.get();
    }

    void Init(URenderer* Renderer);

	URenderer* GetRenderer() const
	{
		return Renderer;
	}

};

template <typename Scene>
    requires std::derived_from<Scene, BaseScene>
void GameManager::ChangeScene()
{
    if (CurrentScene)
    {
        CurrentScene->ExitScene();
    }
    CurrentScene = std::make_unique<Scene>();
    CurrentScene->LoadScene();
}

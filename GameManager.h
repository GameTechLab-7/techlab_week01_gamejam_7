#pragma once

#include <cstdint>
#include <concepts>
#include <memory>

#include "BaseScene.h"
#include "Singleton.h"
#include "URenderer.h"


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

    BaseScene* GetCurrentScene()
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


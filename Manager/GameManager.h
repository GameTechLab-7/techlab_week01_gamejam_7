#pragma once
#include <concepts>
#include <memory>

#include "ObjectManager.h"
#include "URenderer.h"
#include "Scene/BaseScene.h"
#include "AbstractClass/Singleton.h"
#include "GameLogic.h"

/**
 * 
 */
class GameManager : public Singleton<GameManager>
{
private:

    bool bInitialized = false;
    std::unique_ptr<BaseScene> CurrentScene;
    URenderer* Renderer = nullptr;
    std::unique_ptr<class GameLogic> Logic;

public:
    template <typename Scene>
        requires std::derived_from<Scene, BaseScene>
    void ChangeScene();

    BaseScene* GetCurrentScene() const
    {
        return CurrentScene.get();
    }
    template <typename Scene>
        requires std::derived_from<Scene , BaseScene>
    Scene* GetCurrentScene() const
    {
		return static_cast< Scene* >( CurrentScene.get() );
    }

    void Init(URenderer* InRenderer);

	URenderer* GetRenderer() const
	{
		return Renderer;
	}

    void InitGameLogic();
    GameLogic* GetLogic() const { return Logic.get();}
    
};

template <typename Scene>
    requires std::derived_from<Scene, BaseScene>
void GameManager::ChangeScene()
{
    if (CurrentScene)
    {
        ObjectManager::GetInstance().DestroyAll();
        CurrentScene->ExitScene();
    }
    CurrentScene = std::make_unique<Scene>();
    CurrentScene->LoadScene();
}

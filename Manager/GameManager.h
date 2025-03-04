#pragma once
#include <concepts>
#include <memory>

#include "Scene/BaseScene.h"
#include "AbstractClass/Singleton.h"


/**
 * 
 */
class GameManager : public Singleton<GameManager>
{
private:
    std::unique_ptr<BaseScene> CurrentScene;

public:
    template <typename Scene>
        requires std::derived_from<Scene, BaseScene>
    void ChangeScene();

    BaseScene* GetCurrentScene() const
    {
        return CurrentScene.get();
    }

    void Init();
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

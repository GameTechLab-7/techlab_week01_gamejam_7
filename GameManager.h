#pragma once

#include <cstdint>
#include <concepts>
#include <memory>

#include "BaseScene.h"
#include "Singleton.h"


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

    BaseScene* GetCurrentScene()
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


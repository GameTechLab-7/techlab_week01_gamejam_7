#pragma once
#include <memory>
#include "enum.h"
#include "BaseScene.h"
#include "InputSystem.h"

class Player;
class MonsterSpawner;

class MainGameScene : public BaseScene
{

public:
    virtual void LoadScene() override;
    virtual void ExitScene() override;

public:
    MainGameScene() = default;
    
    std::unique_ptr<InputHandler> InputHandlerInstance;

private:

    virtual void Update(float DeltaTime) override;
    virtual void Render() override;
    void RenderWall(class URenderer* Renderer);


	Player* LeftPlayer;
	Player* RightPlayer;
    std::unique_ptr<MonsterSpawner> Spawner;
    

public:
    Player* GetPlayer(EWorld WorldType) const;
	MonsterSpawner* GetSpawner() const { return Spawner.get(); }
};

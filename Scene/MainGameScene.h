#pragma once
#include <memory>
#include "enum.h"
#include "BaseScene.h"

class Player;
class Enemy;
class MonsterSpawner;

class MainGameScene : public BaseScene
{
public:
    virtual void LoadScene() override;
    virtual void ExitScene() override;

private:

    virtual void Update(float DeltaTime) override;
    virtual void Render() override;

	Player* LeftPlayer;
	Player* RightPlayer;
    std::shared_ptr<MonsterSpawner> Spawner;
    

public:
    Player* GetPlayer(EWorld WorldType) const;
};

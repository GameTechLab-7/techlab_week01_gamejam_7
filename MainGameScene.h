#pragma once
#include "BaseScene.h"
#include <vector>
#include <memory>

class Player;
class Enemy;

class MainGameScene :
    public BaseScene
{
    // BaseScene을(를) 통해 상속됨
    void LoadScene() override;
    void ExitScene() override;

private:

    void Update(float deltaTime) override;
    // BaseScene을(를) 통해 상속됨
    void Render() override;

	std::shared_ptr<Player> leftPlayer;
	std::shared_ptr<Player> rightPlayer;

};


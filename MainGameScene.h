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
    std::shared_ptr<Player> left;
    std::shared_ptr<Player> right;

    std::vector<std::shared_ptr<Enemy>> enemies;



    void Update(float deltaTime) override;
    // BaseScene을(를) 통해 상속됨
    void Render() override;



};


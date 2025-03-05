#pragma once
#include <memory>
#include "BaseScene.h"

class Player;
class Enemy;


class MainGameScene : public BaseScene
{
    virtual void LoadScene() override;
    virtual void ExitScene() override;

private:

    virtual void Update(float DeltaTime) override;
    virtual void Render() override;

	Player* leftPlayer;
	Player* rightPlayer;
};

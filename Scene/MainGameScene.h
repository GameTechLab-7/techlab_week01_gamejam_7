#pragma once
#include <memory>
#include "BaseScene.h"
#include "InputSystem.h"

class Player;
class Enemy;


class MainGameScene : public BaseScene
{

    virtual void LoadScene() override;
    virtual void ExitScene() override;

public:
    MainGameScene();
    
    InputHandler* InputHandlerInstance;

private:

    virtual void Update(float DeltaTime) override;
    virtual void Render() override;
    void RenderWall(class URenderer* Renderer);

	Player* leftPlayer;
	Player* rightPlayer;

};

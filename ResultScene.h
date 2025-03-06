#pragma once
#include "Scene/BaseScene.h"

class ResultScene :
    public Scene<Result>
{
    // BaseScene을(를) 통해 상속됨
    void LoadScene() override;
    void ExitScene() override;
    void Render() override;

public:
	void OnClickQuit(); // 종료
    void OnClickRestart(); // 프리셋으로 넘어가게
};


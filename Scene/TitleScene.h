#pragma once
#include "BaseScene.h"


class TitleScene : public BaseScene
{
    virtual void LoadScene() override;
    virtual void ExitScene() override;
    virtual void Render() override;

public:
	void OnClickQuit(); // 종료
	void OnClickStart(); // 프리셋으로 넘어가게
};

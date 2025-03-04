#pragma once
#include "BaseScene.h"
class PresetScene :
    public BaseScene
{
    // BaseScene을(를) 통해 상속됨
    void LoadScene() override;
    void ExitScene() override;
    void Render() override;
};


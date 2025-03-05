#pragma once
#include "BaseScene.h"


class PresetScene : public BaseScene
{
    virtual void LoadScene() override;
    virtual void ExitScene() override;
    virtual void Render() override;
};

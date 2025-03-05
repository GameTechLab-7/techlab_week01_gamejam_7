#pragma once
#include "BaseScene.h"


class PresetScene : public BaseScene
{
public:
	PresetScene() = default;

public:
    virtual void LoadScene() override;
    virtual void ExitScene() override;
    virtual void Render() override;
};  

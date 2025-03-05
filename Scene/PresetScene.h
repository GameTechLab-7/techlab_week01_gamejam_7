#pragma once
#include "BaseScene.h"



class PresetScene : public BaseScene
{
public:
	PresetScene() = default;

    int Player1Preset = 0;
    int Player2Preset = 0;
public:
    virtual void LoadScene() override;
    virtual void ExitScene() override;
    virtual void Render() override;

public:
    //void SelectPreset(EWorld world , int Preset);
};  

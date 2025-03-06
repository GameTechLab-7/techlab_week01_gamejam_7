#pragma once
#include "BaseScene.h"


class TitleScene : public BaseScene
{
    virtual void LoadScene() override;
    virtual void ExitScene() override;
    virtual void Render() override;

    virtual EScene GetCurrentSceneEnum() const override {
        return EScene::Title;
    }
};

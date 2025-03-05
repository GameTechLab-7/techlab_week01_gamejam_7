#pragma once
#include "GameObject/CircleObject.h"
#include "URenderer.h"


class Bullet : public CircleObject
{
public:
    Bullet(EWorld selectedWorld);

    virtual void Render(const URenderer& Renderer) const override;

protected:
    int Damage = 1;
};

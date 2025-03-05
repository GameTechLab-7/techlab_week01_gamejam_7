#include "GameObject/Bullet/Bullet.h"


Bullet::Bullet(EWorld selectedWorld) : CircleObject(selectedWorld)
{
}

void Bullet::Render(const URenderer& Renderer) const
{
    Renderer.UpdateConstant(Location , Radius, Radian);
    ID3D11Buffer* buffer = Renderer.GetVertexBuffer(EObjectType::Bullet);
    int NumOfVertices = Renderer.GetBufferSize(EObjectType::Bullet);
    if(buffer != nullptr)
    {
        Renderer.RenderPrimitive(buffer, NumOfVertices);
    }
}

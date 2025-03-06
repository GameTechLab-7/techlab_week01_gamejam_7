#include "UIObject.h"

UIObject::UIObject(EScene currentScene) {
    MyScene = currentScene;
}

void UIObject::Render(const URenderer& Renderer) const {
    Renderer.UpdateConstant(Location , Scale, 0);
    ID3D11Buffer* buffer = Renderer.GetVertexBuffer(EObjectType::UI);
    int NumOfVertices = Renderer.GetBufferSize(EObjectType::UI);

    //std::cout  << ( buffer != nullptr )  << "\n";
    if (buffer != nullptr)
    {
        Renderer.RenderPrimitive(buffer , NumOfVertices);
    }
}

void UIObject::Update(float DeltaTime) {

}
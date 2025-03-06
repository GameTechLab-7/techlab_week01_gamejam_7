#include "UIObject.h"

UIObject::UIObject(EScene currentScene) {
    MyScene = currentScene;

    Texture = UTexture2D::LoadTargaFromFile("Assets/Texture/default.tga");
    Texture->SetPrimitiveType(EObjectType::UI);
}

void UIObject::Render(const URenderer& Renderer) const {
    Renderer.UpdateConstant(Location , Scale, 0);
    Texture->Render(Renderer);
}

void UIObject::Update(float DeltaTime) {

}
#include "UIObject.h"

#include "Manager/ResourceManager.h"

UIObject::UIObject(EScene currentScene) {
    MyScene = currentScene;

    Texture = ResourceManager::GetInstance().LoadTargaFromFile("Assets/Texture/default.tga");
    Texture->SetPrimitiveType(EObjectType::UI);
}

void UIObject::Render(const URenderer& Renderer) const {
    Renderer.UpdateConstant(Location , Scale, 0);
    Texture->Render(Renderer);
}

void UIObject::Update(float DeltaTime) {

}

void UIObject::SetTexture(const char* FileName)
{
    Texture = ResourceManager::GetInstance().LoadTargaFromFile(FileName);
    Texture->SetPrimitiveType(EObjectType::UI);
}

#include "Manager/UIManager.h"
#include "Manager/GameManager.h"

void UIManager::Initialize(URenderer* renderer) {
	Renderer = renderer;
}

void UIManager::Update(float DeltaTime) {
	ProcessUpdate(DeltaTime);

	ProcessRender();
}

void UIManager::ProcessUpdate(float DeltaTime)
{
    EScene sceneEnum = GameManager::GetInstance().GetCurrentSceneEnum();
    if (!UIObjectsMap.contains(sceneEnum)) {
        return;
    }
    for (auto& Object : UIObjectsMap.at((int)sceneEnum))
    {
        if (InputSystem::GetInstance().GetMouseDown()) {
            if (CheckMouseInBound(InputSystem::GetInstance().GetMouseDownRatioPos() , Object->GetLocation(), Object->GetScale())) {
                //위치 확인해서 펑션 ㄱㄱ
                Object->OnClick();
            }
        }
        Object->Update(DeltaTime);
    }
}

bool UIManager::CheckMouseInBound(FVector3 mouseVec , FVector3 RectLocation , FVector3 Scale) {
    //
    // 위치에서 
    if (mouseVec.x < RectLocation.x - Scale.y || mouseVec.x > RectLocation.x + Scale.y) {
        return false;
    }
    if (mouseVec.y < -RectLocation.y - Scale.z || mouseVec.y > -RectLocation.y + Scale.z) {
        return false;
    }
    return true;
}


void UIManager::ProcessRender() const
{
    if (Renderer == nullptr)
    {
        return;
    }

    EScene sceneEnum = GameManager::GetInstance().GetCurrentSceneEnum();
    if (!UIObjectsMap.contains(sceneEnum)) {
        return;
    }
    Renderer->PrepareUIViewport();
    
    for (const auto Object : UIObjectsMap.at(( int ) sceneEnum))
    {
        Object->Render(*Renderer);
    }
}

#pragma once
#include <memory>
#include <functional>
#include "URenderer.h"
#include "Texture/UTexture2D.h"

class UIObject : public std::enable_shared_from_this<UIObject>
{
public:
	UIObject(EScene CurrentScene);
	virtual ~UIObject() = default;

	void Render(const URenderer& Renderer) const;
	void Update(float DeltaTime);
	
	void SetLocation(const FVector3& NewLocation) { Location = NewLocation; }
	void SetScale(const FVector3& NewScale) { Scale = NewScale; }

	FVector3 GetLocation() { return Location; }
	FVector3 GetScale() { return Scale; }

	void OnClick() { if(OnClickEvent != nullptr) OnClickEvent(); }
	void SetOnClickEvent(void(*Fn)()) { OnClickEvent = Fn; }
private:
	std::unique_ptr<UTexture2D> Texture;

	FVector3 Location;
	FVector3 Scale;
	EScene MyScene;
	
	void(*OnClickEvent)() = nullptr;
};

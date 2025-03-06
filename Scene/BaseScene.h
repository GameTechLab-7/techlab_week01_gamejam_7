#pragma once
#include <string>
#include "ImGui/imgui.h"
#include "Imgui/imgui_internal.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"

#include "Enum.h"

class BaseScene
{
public:
	BaseScene() = default;
	virtual ~BaseScene() = default;

	// 이동 & 복사 생성자 제거
	BaseScene(const BaseScene&) = delete;
	BaseScene& operator=(const BaseScene&) = delete;
	BaseScene(BaseScene&&) = delete;
	BaseScene& operator=(BaseScene&&) = delete;

	virtual void LoadScene() = 0;
	virtual void ExitScene() = 0;
	virtual void Update(float DeltaTime);
	virtual void Render() = 0;

	std::string GetName() const { return Name; }
	void SetName(const char* name) { Name = name; }

	virtual EScene GetCurrentSceneEnum() const = 0;


protected:
	std::string Name;

};


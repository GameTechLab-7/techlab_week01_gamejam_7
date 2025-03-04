#pragma once
#include <string>


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


protected:
	std::string Name;

};


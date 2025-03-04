#pragma once
#include <string>


class BaseScene
{
public:
	virtual ~BaseScene() = default;

	// 이동 & 복사 생성자 제거
	//BaseScene(const BaseScene&) = default;
	//BaseScene& operator=(const BaseScene&) = default;
	//BaseScene(BaseScene&&) = default;
	//BaseScene& operator=(BaseScene&&) = default;

	virtual void LoadScene() = 0;
	virtual void ExitScene() = 0;
	virtual void Update(float deltaTime);
	virtual void Render() = 0;


protected:
	std::string Name;

};


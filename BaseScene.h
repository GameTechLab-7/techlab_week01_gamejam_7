#pragma once
#include <string>


class BaseScene
{
public:
	virtual void LoadScene() = 0;
	virtual void ExitScene() = 0;
	virtual void Update(float deltaTime);
	virtual void Render() = 0;


protected:
	std::string Name;

};


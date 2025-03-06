#pragma once
#include "Texture/UTexture2D.h"
#include <memory>

class BackGround
{
public:
	BackGround();
	~BackGround() = default;

	void Render();
private:
	std::shared_ptr<UTexture2D> Texture;
};


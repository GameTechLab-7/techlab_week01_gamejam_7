#pragma once
#include <memory>
#include <unordered_map>

#include "AbstractClass/Singleton.h"


class UTexture2D;

class ResourceManager : public Singleton<ResourceManager>
{
public:
    std::shared_ptr<UTexture2D> LoadTargaFromFile(const char* FileName);

private:
    using CachedTextures = std::unordered_map<const char*, std::shared_ptr<UTexture2D>>;
    CachedTextures Textures;
};

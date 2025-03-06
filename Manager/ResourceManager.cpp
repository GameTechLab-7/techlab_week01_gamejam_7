#include "ResourceManager.h"

#include "Texture/UTexture2D.h"


std::shared_ptr<UTexture2D> ResourceManager::LoadTargaFromFile(const char* FileName)
{
    if (!Textures.contains(FileName))
    {
        Textures[FileName].reset(UTexture2D::LoadTargaFromFile(FileName));
    }
    return Textures[FileName];
}

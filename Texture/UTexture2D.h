#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <memory>
#include <vector>

#include "Enum.h"


class URenderer;

class UTexture2D
{
private:
    struct TargaHeader
    {
        unsigned char Data1[12];
        unsigned short Width;
        unsigned short Height;
        unsigned char Bpp;
        unsigned char Data2;
    };

    friend class ResourceManager;

public:
    UTexture2D() = default;

    void Render(const URenderer& Renderer) const;

public:
    uint32_t GetTextureWidth() const { return Width; }
    uint32_t GetTextureHeight() const { return Height; }

    void SetPrimitiveType(EObjectType NewPrimitiveType) { PrimitiveType = NewPrimitiveType; }

private:
    static UTexture2D* LoadTargaFromFile(const char* FileName);

    /**
     * Targa 이미지 파일을 불러옵니다.
     * @return Targa Data
     */
    std::unique_ptr<uint8_t[]> LoadTarga(const char* FileName);
    void CreateShaderResource(std::unique_ptr<uint8_t[]> InData);

private:
    EObjectType PrimitiveType = EObjectType::Enemy;  // 사각형

    uint32_t Width;
    uint32_t Height;

    Microsoft::WRL::ComPtr<ID3D11Texture2D> Texture;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> TextureResourceView;
};

#include "UTexture2D.h"
#include <cstdint>
#include <stdexcept>
#include "URenderer.h"
#include "Manager/GameManager.h"

#define IF_FAILED_THROW_ERROR(Expr, Msg) \
    if (!(Expr)) throw std::runtime_error(Msg)


void UTexture2D::Render(const URenderer& Renderer) const
{
    if (!TextureResourceView) return;

    Renderer.GetDeviceContext()->PSSetShaderResources(0, 1, TextureResourceView.GetAddressOf());
    Renderer.RenderPrimitive(Renderer.GetVertexBuffer(PrimitiveType), Renderer.GetBufferSize(PrimitiveType));
}

std::unique_ptr<UTexture2D> UTexture2D::LoadTargaFromFile(const char* FileName)
{
    auto Texture = std::make_unique<UTexture2D>();
    Texture->CreateShaderResource(Texture->LoadTarga(FileName));
    return Texture;
}

std::unique_ptr<uint8_t[]> UTexture2D::LoadTarga(const char* FileName)
{
    // targa 파일을 바이너리 모드로 파일을 엽니다.
    FILE* FilePtr;

    fopen_s(&FilePtr, FileName, "rb");
    if (!FilePtr) throw std::runtime_error("Error opening file!");
 
    // 파일 헤더를 읽어옵니다.
    TargaHeader TargaFileHeader;
    uint32_t count = static_cast<uint32_t>(fread(&TargaFileHeader, sizeof(TargaHeader), 1, FilePtr));
    IF_FAILED_THROW_ERROR(
        count == 1,
        "Error reading targa file!"
    );
 
    // 파일헤더에서 중요 정보를 얻어옵니다.
    Height = static_cast<int>(TargaFileHeader.Height);
    Width = static_cast<int>(TargaFileHeader.Width);
 
    // 파일이 32bit 인지 24bit인지 체크합니다.
    IF_FAILED_THROW_ERROR(
        TargaFileHeader.Bpp == 32,
        "Error targa file is not 32 bit!"
    );
 
    // 32 비트 이미지 데이터의 크기를 계산합니다.
    const uint32_t ImageSize = Width * Height * 4;
 
    // targa 이미지를 넣을 공간을 할당합니다.
    uint8_t* TargaImage = new uint8_t[ImageSize];
    IF_FAILED_THROW_ERROR(
        TargaImage,
        "Error allocating memory for targa image data!"
    );
 
    // targa 이미지 데이터를 읽습니다.
    count = static_cast<uint32_t>(fread(TargaImage, 1, ImageSize, FilePtr));
    IF_FAILED_THROW_ERROR(
        count == ImageSize,
        "Error reading targa image data!"
    );
 
    // 파일을 닫습니다.
    IF_FAILED_THROW_ERROR(
        fclose(FilePtr) == 0,
        "Error closing file!"
    );
 
    // targa 대상 데이터에 대한 메모리를 할당합니다.
    std::unique_ptr<uint8_t[]> TargaData = std::make_unique<uint8_t[]>(ImageSize);
 
    // targa 대상 데이터 배열에 인덱스를 초기화합니다.
    size_t Index = 0;
 
    // targa 이미지 데이터에 인덱스를 초기화합니다.
    uint32_t k = Width * Height * 4 - (Width * 4);
 
    // 이제 targa 형식이 거꾸로 저장되었으므로 올바른 순서로 targa 이미지 데이터를 targa 대상 배열에 복사합니다.
    for (uint32_t j = 0; j < Height; j++)
    {
        for (uint32_t i = 0; i < Width; i++)
        {
            TargaData[Index + 0] = TargaImage[k + 2];  // R
            TargaData[Index + 1] = TargaImage[k + 1];  // G
            TargaData[Index + 2] = TargaImage[k + 0];  // B
            TargaData[Index + 3] = TargaImage[k + 3];  // A
 
            // 인덱스를 targa 데이터로 증가시킵니다.
            k += 4;
            Index += 4;
        }
 
        // targa 이미지 데이터 인덱스를 역순으로 읽은 후 열의 시작 부분에서 이전 행으로 다시 설정합니다.
        k -= Width * 8;
    }
 
    // 대상 배열에 복사 된 targa 이미지 데이터를 해제합니다.
    delete[] TargaImage;
    TargaImage = nullptr;

    return TargaData;
}

void UTexture2D::CreateShaderResource(std::unique_ptr<uint8_t[]> InData)
{
    const URenderer* Renderer = GameManager::GetInstance().GetRenderer();

    // 텍스처의 구조체를 설정합니다.
    D3D11_TEXTURE2D_DESC TextureDesc{
        .Width = Width,
        .Height = Height,
        .MipLevels = 0,
        .ArraySize = 1,
        .Format = DXGI_FORMAT_R8G8B8A8_UNORM,
        .SampleDesc = {
            .Count = 1,
            .Quality = 0
        },
        .Usage = D3D11_USAGE_DEFAULT,
        .BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET,
        .CPUAccessFlags = 0,
        .MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS
    };

    // 빈 텍스처를 생성합니다.
    HRESULT hResult = Renderer->GetDevice()->CreateTexture2D(&TextureDesc, nullptr, Texture.GetAddressOf());
    IF_FAILED_THROW_ERROR(
        SUCCEEDED(hResult),
        "Error creating texture!"
    );

    // targa 이미지 데이터의 너비 사이즈를 설정합니다.
    uint32_t RowPitch = (Width * 4) * sizeof(uint8_t);

    // targa 이미지 데이터를 텍스처에 복사합니다.
    Renderer->GetDeviceContext()->UpdateSubresource(Texture.Get(), 0, nullptr, InData.get(), RowPitch, 0);

    // 셰이더 리소스 뷰 구조체를 설정합니다.
    D3D11_SHADER_RESOURCE_VIEW_DESC SrvDesc;
    SrvDesc.Format = TextureDesc.Format;
    SrvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    SrvDesc.Texture2D.MostDetailedMip = 0;
    SrvDesc.Texture2D.MipLevels = -1;

    // 텍스처의 셰이더 리소스 뷰를 만듭니다.
    hResult = Renderer->GetDevice()->CreateShaderResourceView(Texture.Get(), &SrvDesc, TextureResourceView.GetAddressOf());
    IF_FAILED_THROW_ERROR(
        SUCCEEDED(hResult),
        "Error creating shader resource view!"
    );

    // 이 텍스처에 대해 밉맵을 생성합니다.
    Renderer->GetDeviceContext()->GenerateMips(TextureResourceView.Get());
}

#undef IF_FAILED_THROW_ERROR

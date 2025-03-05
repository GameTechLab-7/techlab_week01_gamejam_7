#include "URenderer.h"
#include <d3dcompiler.h>

using Microsoft::WRL::ComPtr;


struct alignas( 16 ) URenderer::FConstants
{
    FVector3 Offset;
    float Scale;
    float Radian;
    float Padding;
    int bIsHit;
};

/** Renderer를 초기화 합니다. */
void URenderer::Create(HWND hWindow)
{
    CreateDeviceAndSwapChain(hWindow);
    CreateFrameBuffer();
    CreateRasterizerState();

    Cache = std::make_unique<BufferCache>();
}

/** Renderer에 사용된 모든 리소스를 해제합니다. */
void URenderer::Release()
{
    ReleaseRasterizerState();

    // 렌더 타겟을 초기화
    DeviceContext->OMSetRenderTargets(0 , nullptr , nullptr);

    ReleaseFrameBuffer();
    ReleaseDeviceAndSwapChain();
}

void URenderer::CreateShader()
{
    /**
     * 컴파일된 셰이더의 바이트코드를 저장할 변수 (ID3DBlob)
     *
     * 범용 메모리 버퍼를 나타내는 형식
     *   - 여기서는 shader object bytecode를 담기위해 쓰임
     * 다음 두 메서드를 제공한다.
     *   - LPVOID GetBufferPointer
     *     - 버퍼를 가리키는 void* 포인터를 돌려준다.
     *   - SIZE_T GetBufferSize
     *     - 버퍼의 크기(바이트 갯수)를 돌려준다
     */

    // Texture Shader 생성
    {
        ComPtr<ID3DBlob> VertexShaderCSO;
        ComPtr<ID3DBlob> PixelShaderCSO;

        D3DCompileFromFile(L"Shaders/TextureShader.hlsl", nullptr, nullptr, "TextureShaderVS", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &VertexShaderCSO, nullptr);
        Device->CreateVertexShader(VertexShaderCSO->GetBufferPointer(), VertexShaderCSO->GetBufferSize(), nullptr, &TextureVertexShader);
    
        D3DCompileFromFile(L"Shaders/TextureShader.hlsl", nullptr, nullptr, "TextureShaderPS", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &PixelShaderCSO, nullptr);
        Device->CreatePixelShader(PixelShaderCSO->GetBufferPointer(), PixelShaderCSO->GetBufferSize(), nullptr, &TexturePixelShader);

        D3D11_INPUT_ELEMENT_DESC Layout[] =
        {
            {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
        };

        Device->CreateInputLayout(Layout , ARRAYSIZE(Layout) , VertexShaderCSO->GetBufferPointer() , VertexShaderCSO->GetBufferSize() , &TextureInputLayout);

        D3D11_SAMPLER_DESC SamplerDesc{
            .Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR,
            .AddressU = D3D11_TEXTURE_ADDRESS_WRAP,
            .AddressV = D3D11_TEXTURE_ADDRESS_WRAP,
            .AddressW = D3D11_TEXTURE_ADDRESS_WRAP,
            .MipLODBias = 0.0f,
            .MaxAnisotropy = 1,
            .ComparisonFunc = D3D11_COMPARISON_ALWAYS,
            .BorderColor = {0, 0, 0, 0},
            .MinLOD = 0,
            .MaxLOD = D3D11_FLOAT32_MAX
        };

        Device->CreateSamplerState(&SamplerDesc, &TextureSamplerState);
    }

    // 정점 하나의 크기를 설정 (바이트 단위)
    Stride = sizeof(FVertexSimple);
}
void URenderer::ReleaseShader()
{
    if (TextureInputLayout)
    {
        TextureInputLayout->Release();
        TextureInputLayout = nullptr;
    }

    if (TexturePixelShader)
    {
        TexturePixelShader->Release();
        TexturePixelShader = nullptr;
    }

    if (TextureVertexShader)
    {
        TextureVertexShader->Release();
        TextureVertexShader = nullptr;
    }

    if (TextureSamplerState)
    {
        TextureSamplerState->Release();
        TextureSamplerState = nullptr;
    }
}

void URenderer::CreateConstantBuffer()
{
    D3D11_BUFFER_DESC ConstantBufferDesc = {};
    ConstantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;                        // 매 프레임 CPU에서 업데이트 하기 위해
    ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;             // 상수 버퍼로 설정
    ConstantBufferDesc.ByteWidth = sizeof(FConstants) + 0xf & 0xfffffff0;  // 16byte의 배수로 올림
    ConstantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;            // CPU에서 쓰기 접근이 가능하게 설정

    Device->CreateBuffer(&ConstantBufferDesc , nullptr , &ConstantBuffer);
}
void URenderer::ReleaseConstantBuffer()
{
    if (ConstantBuffer)
    {
        ConstantBuffer->Release();
        ConstantBuffer = nullptr;
    }
}

/** 스왑 체인의 백 버퍼와 프론트 버퍼를 교체하여 화면에 출력 */
void URenderer::SwapBuffer() const
{
    SwapChain->Present(1 , 0); // SyncInterval: VSync 활성화 여부
}

/** 렌더링 파이프라인을 준비 합니다. */
void URenderer::Prepare() const
{
    // 화면 지우기
    DeviceContext->ClearRenderTargetView(FrameBufferRTV , ClearColor);

    // InputAssembler의 Vertex 해석 방식을 설정
    DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    /**
     * OutputMerger 설정
     * 렌더링 파이프라인의 최종 단계로써, 어디에 그릴지(렌더 타겟)와 어떻게 그릴지(블렌딩)를 지정
     */
    DeviceContext->OMSetRenderTargets(1 , &FrameBufferRTV , nullptr);
    DeviceContext->OMSetBlendState(nullptr , nullptr , 0xffffffff);
}

void URenderer::PrepareLine() const {
    // InputAssembler의 Vertex 해석 방식을 설정
}

void URenderer::PrepareViewport(EWorld World) const
{
    const D3D11_VIEWPORT ViewPort = viewports.at(World);
    // Rasterization할 Viewport를 설정 
    DeviceContext->RSSetViewports(1 , &ViewPort);
    DeviceContext->RSSetState(RasterizerState);

}

/** 셰이더를 준비 합니다. */
void URenderer::PrepareShader() const
{
    // 기본 셰이더랑 InputLayout을 설정
    DeviceContext->VSSetShader(TextureVertexShader , nullptr , 0);
    DeviceContext->PSSetShader(TexturePixelShader , nullptr , 0);
    DeviceContext->PSSetSamplers(0, 1, &TextureSamplerState);
    DeviceContext->IASetInputLayout(TextureInputLayout);

    // 버텍스 쉐이더에 상수 버퍼를 설정
    if (ConstantBuffer)
    {
        DeviceContext->VSSetConstantBuffers(0 , 1 , &ConstantBuffer);
    }
}

/**
 * Buffer에 있는 Vertex를 그립니다.
 * @param pBuffer 렌더링에 사용할 버텍스 버퍼에 대한 포인터
 * @param numVertices 버텍스 버퍼에 저장된 버텍스의 총 개수
 */
void URenderer::RenderPrimitive(ID3D11Buffer* pBuffer , UINT numVertices) const
{
    UINT Offset = 0;
    DeviceContext->IASetVertexBuffers(0 , 1 , &pBuffer , &Stride , &Offset);
    DeviceContext->Draw(numVertices , 0);
}

/**
 * 정점 데이터로 Vertex Buffer를 생성합니다.
 * @param Vertices 버퍼로 변환할 정점 데이터 배열의 포인터
 * @param ByteWidth 버퍼의 총 크기 (바이트 단위)
 * @return 생성된 버텍스 버퍼에 대한 ID3D11Buffer 포인터, 실패 시 nullptr
 *
 * @note 이 함수는 D3D11_USAGE_IMMUTABLE 사용법으로 버퍼를 생성합니다.
 */
ID3D11Buffer* URenderer::CreateVertexBuffer(const FVertexSimple* Vertices , UINT ByteWidth) const
{
    D3D11_BUFFER_DESC VertexBufferDesc = {};
    VertexBufferDesc.ByteWidth = ByteWidth;
    VertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
    VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA VertexBufferSRD = {};
    VertexBufferSRD.pSysMem = Vertices;

    ID3D11Buffer* VertexBuffer;
    const HRESULT Result = Device->CreateBuffer(&VertexBufferDesc , &VertexBufferSRD , &VertexBuffer);
    if (FAILED(Result))
    {
        return nullptr;
    }
    return VertexBuffer;
}

/** Buffer를 해제합니다. */
void URenderer::ReleaseVertexBuffer(ID3D11Buffer* pBuffer) const
{
    pBuffer->Release();
}

/** Constant Data를 업데이트 합니다. */
void URenderer::UpdateConstant(const FVector3& Offset , float Scale, float Radian, bool bIsHit) const
{
    if (!ConstantBuffer) return;

    D3D11_MAPPED_SUBRESOURCE ConstantBufferMSR;

    // 상수 버퍼를 CPU 메모리에 매핑
    // D3D11_MAP_WRITE_DISCARD는 이전 내용을 무시하고 새로운 데이터로 덮어쓰기 위해 사용
    DeviceContext->Map(ConstantBuffer , 0 , D3D11_MAP_WRITE_DISCARD , 0 , &ConstantBufferMSR);
    {
        // 매핑된 메모리를 FConstants 구조체로 캐스팅
        FConstants* Constants = static_cast< FConstants* >( ConstantBufferMSR.pData );
        Constants->Offset = Offset;
        Constants->Scale = Scale;
        Constants->Radian = Radian;
		Constants->bIsHit = bIsHit;
    }
    DeviceContext->Unmap(ConstantBuffer , 0);
}

ID3D11Device* URenderer::GetDevice() const
{
    return Device;
}

ID3D11DeviceContext* URenderer::GetDeviceContext() const
{
    return DeviceContext;
}

/** Direct3D Device 및 SwapChain을 생성합니다. */
void URenderer::CreateDeviceAndSwapChain(HWND hWindow)
{
    // 지원하는 Direct3D 기능 레벨을 정의
    D3D_FEATURE_LEVEL FeatureLevels[ ] = { D3D_FEATURE_LEVEL_11_0 };

    // SwapChain 구조체 초기화
    DXGI_SWAP_CHAIN_DESC SwapChainDesc = {};
    SwapChainDesc.BufferDesc.Width = 0;                            // 창 크기에 맞게 자동으로 설정
    SwapChainDesc.BufferDesc.Height = 0;                           // 창 크기에 맞게 자동으로 설정
    SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // 색상 포멧
    SwapChainDesc.SampleDesc.Count = 1;                            // 멀티 샘플링 비활성화
    SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;   // 렌더 타겟으로 설정
    SwapChainDesc.BufferCount = 2;                                 // 더블 버퍼링
    SwapChainDesc.OutputWindow = hWindow;                          // 렌더링할 창 핸들
    SwapChainDesc.Windowed = TRUE;                                 // 창 모드
    SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;      // 스왑 방식

    // Direct3D Device와 SwapChain을 생성
    D3D11CreateDeviceAndSwapChain(
        // 입력 매개변수
        nullptr ,                                                       // 디바이스를 만들 때 사용할 비디오 어댑터에 대한 포인터
        D3D_DRIVER_TYPE_HARDWARE ,                                      // 만들 드라이버 유형을 나타내는 D3D_DRIVER_TYPE 열거형 값
        nullptr ,                                                       // 소프트웨어 래스터라이저를 구현하는 DLL에 대한 핸들
        D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG ,  // 사용할 런타임 계층을 지정하는 D3D11_CREATE_DEVICE_FLAG 열거형 값들의 조합
        FeatureLevels ,                                                 // 만들려는 기능 수준의 순서를 결정하는 D3D_FEATURE_LEVEL 배열에 대한 포인터
        ARRAYSIZE(FeatureLevels) ,                                      // pFeatureLevels 배열의 요소 수
        D3D11_SDK_VERSION ,                                             // SDK 버전. 주로 D3D11_SDK_VERSION을 사용
        &SwapChainDesc ,                                                // SwapChain 설정과 관련된 DXGI_SWAP_CHAIN_DESC 구조체에 대한 포인터

        // 출력 매개변수
        &SwapChain ,                                                    // 생성된 IDXGISwapChain 인터페이스에 대한 포인터
        &Device ,                                                       // 생성된 ID3D11Device 인터페이스에 대한 포인터
        nullptr ,                                                       // 선택된 기능 수준을 나타내는 D3D_FEATURE_LEVEL 값을 반환
        &DeviceContext                                                 // 생성된 ID3D11DeviceContext 인터페이스에 대한 포인터
    );

    // 생성된 SwapChain의 정보 가져오기
    SwapChain->GetDesc(&SwapChainDesc);

        // 뷰포트 정보 설정
        viewports.insert({ EWorld::First, {
            -( static_cast< float >( SwapChainDesc.BufferDesc.Width ) / 2.0f ), 0.0f,
            static_cast< float >( SwapChainDesc.BufferDesc.Width ), static_cast< float >( SwapChainDesc.BufferDesc.Height ),
            0.0f, 1.0f
        } });

        viewports.insert({ EWorld::Second, {
            static_cast< float >( SwapChainDesc.BufferDesc.Width ) / 2.0f, 0.0f,
            static_cast< float >( SwapChainDesc.BufferDesc.Width ), static_cast< float >( SwapChainDesc.BufferDesc.Height ),
            0.0f, 1.0f
        } });
    }

/** Direct3D Device 및 SwapChain을 해제합니다.  */
void URenderer::ReleaseDeviceAndSwapChain()
{
    if (DeviceContext)
    {
        DeviceContext->Flush(); // 남이있는 GPU 명령 실행
    }

    if (SwapChain)
    {
        SwapChain->Release();
        SwapChain = nullptr;
    }

    if (Device)
    {
        Device->Release();
        Device = nullptr;
    }

    if (DeviceContext)
    {
        DeviceContext->Release();
        DeviceContext = nullptr;
    }
}

/** 프레임 버퍼를 생성합니다. */
void URenderer::CreateFrameBuffer()
{
    // 스왑 체인으로부터 백 버퍼 텍스처 가져오기
    SwapChain->GetBuffer(0 , IID_PPV_ARGS(&FrameBuffer));

    // 렌더 타겟 뷰 생성
    D3D11_RENDER_TARGET_VIEW_DESC FrameBufferRTVDesc = {};
    FrameBufferRTVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;      // 색상 포맷
    FrameBufferRTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D; // 2D 텍스처

    Device->CreateRenderTargetView(FrameBuffer , &FrameBufferRTVDesc , &FrameBufferRTV);
}

/** 프레임 버퍼를 해제합니다. */
void URenderer::ReleaseFrameBuffer()
{
    if (FrameBuffer)
    {
        FrameBuffer->Release();
        FrameBuffer = nullptr;
    }

    if (FrameBufferRTV)
    {
        FrameBufferRTV->Release();
        FrameBufferRTV = nullptr;
    }
}

/** 레스터라이즈 상태를 생성합니다. */
void URenderer::CreateRasterizerState()
{
    D3D11_RASTERIZER_DESC RasterizerDesc = {};
    RasterizerDesc.FillMode = D3D11_FILL_SOLID; // 채우기 모드
    RasterizerDesc.CullMode = D3D11_CULL_BACK;  // 백 페이스 컬링

    Device->CreateRasterizerState(&RasterizerDesc , &RasterizerState);
}

/** 레스터라이저 상태를 해제합니다. */
void URenderer::ReleaseRasterizerState()
{
    if (RasterizerState)
    {
        RasterizerState->Release();
        RasterizerState = nullptr;
    }
}

ID3D11Buffer* URenderer::GetVertexBuffer(EObjectType Type) const
{
    if (Cache.get() == nullptr)
    {
        return nullptr;
    }
    return Cache->GetBuffer(Type);
}

int URenderer::GetBufferSize(EObjectType Type) const
{
    if (Cache.get() == nullptr)
        return 0;

    return Cache->GetBufferSize(Type);
}

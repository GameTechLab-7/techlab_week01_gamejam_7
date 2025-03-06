#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <unordered_map>
#include <memory>

#include "Math/FVector3.h"
#include "Enum.h"
#include "BufferCache.h"
#include "PrimitiveVertices.h"


class URenderer
{
private:
    struct alignas(16) FConstants;

public:
    /** Renderer를 초기화 합니다. */
    void Create(HWND hWindow);

    /** Renderer에 사용된 모든 리소스를 해제합니다. */
    void Release();

    void CreateShader();
    void ReleaseShader();

    void CreateConstantBuffer();

    void ReleaseConstantBuffer();

    /** 스왑 체인의 백 버퍼와 프론트 버퍼를 교체하여 화면에 출력 */
    void SwapBuffer() const;

    /** 렌더링 파이프라인을 준비 합니다. */
    void Prepare() const;

    void PrepareLine() const;

    /** 셰이더를 준비 합니다. */
    void PrepareShader() const;
    void PrepareViewport(EWorld World) const;
    void PrepareUIViewport() const;

    
    ID3D11Buffer* CreateVertexBuffer(const FVertexSimple* Vertices, UINT ByteWidth) const;

    /**
     * Buffer에 있는 Vertex를 그립니다.
     * @param pBuffer 렌더링에 사용할 버텍스 버퍼에 대한 포인터
     * @param numVertices 버텍스 버퍼에 저장된 버텍스의 총 개수
     */
    void RenderPrimitive(ID3D11Buffer* pBuffer, UINT numVertices) const;

    /** Buffer를 해제합니다. */
    void ReleaseVertexBuffer(ID3D11Buffer* pBuffer) const;

    /** Constant Data를 업데이트 합니다. */
    void UpdateConstant(const FVector3& Offset , FVector3 Scale , float Radian) const;
    void UpdateConstant(const FVector3& Offset, float Scale, float Radian) const;

public:
    /*버텍스버퍼 가져오기*/
    ID3D11Buffer* GetVertexBuffer(EObjectType Type) const;

    /*버텍스 개수 가져오기*/
    int GetBufferSize(EObjectType Type) const;

    ID3D11Device* GetDevice() const;
    ID3D11DeviceContext* GetDeviceContext() const;

protected:
    /** Direct3D Device 및 SwapChain을 생성합니다. */
    void CreateDeviceAndSwapChain(HWND hWindow);

    /** Direct3D Device 및 SwapChain을 해제합니다.  */
    void ReleaseDeviceAndSwapChain();

    /** 프레임 버퍼를 생성합니다. */
    void CreateFrameBuffer();

    /** 프레임 버퍼를 해제합니다. */
    void ReleaseFrameBuffer();

    /** 레스터라이즈 상태를 생성합니다. */
    void CreateRasterizerState();

    /** 레스터라이저 상태를 해제합니다. */
    void ReleaseRasterizerState();


    // Direct3D 11 장치(Device)와 장치 컨텍스트(Device Context) 및 스왑 체인(Swap Chain)을 관리하기 위한 포인터들
    ID3D11Device* Device = nullptr;                         // GPU와 통신하기 위한 Direct3D 장치
    ID3D11DeviceContext* DeviceContext = nullptr;           // GPU 명령 실행을 담당하는 컨텍스트
    IDXGISwapChain* SwapChain = nullptr;                    // 프레임 버퍼를 교체하는 데 사용되는 스왑 체인

    // 렌더링에 필요한 리소스 및 상태를 관리하기 위한 변수들
    ID3D11Texture2D* FrameBuffer = nullptr;                 // 화면 출력용 텍스처
    ID3D11RenderTargetView* FrameBufferRTV = nullptr;       // 텍스처를 렌더 타겟으로 사용하는 뷰
    ID3D11RasterizerState* RasterizerState = nullptr;       // 래스터라이저 상태(컬링, 채우기 모드 등 정의)
    ID3D11Buffer* ConstantBuffer = nullptr;                 // 쉐이더에 데이터를 전달하기 위한 상수 버퍼

    FLOAT ClearColor[4] = { 0.025f, 0.025f, 0.025f, 1.0f }; // 화면을 초기화(clear)할 때 사용할 색상 (RGBA)

    std::unordered_map<EWorld , D3D11_VIEWPORT> viewports;             // 렌더링 영역을 정의하는 뷰포트 정보
    D3D11_VIEWPORT UIViewPort;

    // Shader를 렌더링할 때 사용되는 변수들
    ID3D11VertexShader* SimpleVertexShader = nullptr;       // Vertex 데이터를 처리하는 Vertex 셰이더
    ID3D11PixelShader* SimplePixelShader = nullptr;         // Pixel의 색상을 결정하는 Pixel 셰이더
    ID3D11InputLayout* SimpleInputLayout = nullptr;         // Vertex 셰이더 입력 레이아웃 정의
    unsigned int Stride = 0;                                // Vertex 버퍼의 각 요소 크기

    // 버텍스버퍼 재사용을 위한 버퍼캐시
    std::unique_ptr<BufferCache> Cache;
};

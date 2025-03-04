#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#include "FVector3.h"

struct FVertexSimple
{
	float x, y, z;    // Position
	float r, g, b, a; // Color
};

class URenderer
{
private:
    struct alignas(16) FConstants;

public:
    /** Renderer�� �ʱ�ȭ �մϴ�. */
    void Create(HWND hWindow);

    /** Renderer�� ���� ��� ���ҽ��� �����մϴ�. */
    void Release();

    void CreateShader();
    void ReleaseShader();

    void CreateConstantBuffer();

    void ReleaseConstantBuffer();

    /** ���� ü���� �� ���ۿ� ����Ʈ ���۸� ��ü�Ͽ� ȭ�鿡 ��� */
    void SwapBuffer() const;

    /** ������ ������������ �غ� �մϴ�. */
    void Prepare() const;

    /** ���̴��� �غ� �մϴ�. */
    void PrepareShader() const;
    
    ID3D11Buffer* CreateVertexBuffer(const FVertexSimple* Vertices, UINT ByteWidth) const;

    /**
     * Buffer�� �ִ� Vertex�� �׸��ϴ�.
     * @param pBuffer �������� ����� ���ؽ� ���ۿ� ���� ������
     * @param numVertices ���ؽ� ���ۿ� ����� ���ؽ��� �� ����
     */
    void RenderPrimitive(ID3D11Buffer* pBuffer, UINT numVertices) const;

    /** Buffer�� �����մϴ�. */
    void ReleaseVertexBuffer(ID3D11Buffer* pBuffer) const;

    /** Constant Data�� ������Ʈ �մϴ�. */
    void UpdateConstant(const FVector3& Offset, float Scale) const;

    ID3D11Device* GetDevice() const;
    ID3D11DeviceContext* GetDeviceContext() const;

protected:
    /** Direct3D Device �� SwapChain�� �����մϴ�. */
    void CreateDeviceAndSwapChain(HWND hWindow);

    /** Direct3D Device �� SwapChain�� �����մϴ�.  */
    void ReleaseDeviceAndSwapChain();

    /** ������ ���۸� �����մϴ�. */
    void CreateFrameBuffer();

    /** ������ ���۸� �����մϴ�. */
    void ReleaseFrameBuffer();

    /** �����Ͷ����� ���¸� �����մϴ�. */
    void CreateRasterizerState();

    /** �����Ͷ����� ���¸� �����մϴ�. */
    void ReleaseRasterizerState();

protected:
    // Direct3D 11 ��ġ(Device)�� ��ġ ���ؽ�Ʈ(Device Context) �� ���� ü��(Swap Chain)�� �����ϱ� ���� �����͵�
    ID3D11Device* Device = nullptr;                         // GPU�� ����ϱ� ���� Direct3D ��ġ
    ID3D11DeviceContext* DeviceContext = nullptr;           // GPU ��� ������ ����ϴ� ���ؽ�Ʈ
    IDXGISwapChain* SwapChain = nullptr;                    // ������ ���۸� ��ü�ϴ� �� ���Ǵ� ���� ü��

    // �������� �ʿ��� ���ҽ� �� ���¸� �����ϱ� ���� ������
    ID3D11Texture2D* FrameBuffer = nullptr;                 // ȭ�� ��¿� �ؽ�ó
    ID3D11RenderTargetView* FrameBufferRTV = nullptr;       // �ؽ�ó�� ���� Ÿ������ ����ϴ� ��
    ID3D11RasterizerState* RasterizerState = nullptr;       // �����Ͷ����� ����(�ø�, ä��� ��� �� ����)
    ID3D11Buffer* ConstantBuffer = nullptr;                 // ���̴��� �����͸� �����ϱ� ���� ��� ����

    FLOAT ClearColor[4] = { 0.025f, 0.025f, 0.025f, 1.0f }; // ȭ���� �ʱ�ȭ(clear)�� �� ����� ���� (RGBA)
    D3D11_VIEWPORT ViewportInfo = {};                       // ������ ������ �����ϴ� ����Ʈ ����

    // Shader�� �������� �� ���Ǵ� ������
    ID3D11VertexShader* SimpleVertexShader = nullptr;       // Vertex �����͸� ó���ϴ� Vertex ���̴�
    ID3D11PixelShader* SimplePixelShader = nullptr;         // Pixel�� ������ �����ϴ� Pixel ���̴�
    ID3D11InputLayout* SimpleInputLayout = nullptr;         // Vertex ���̴� �Է� ���̾ƿ� ����
    unsigned int Stride = 0;                                // Vertex ������ �� ��� ũ��
};
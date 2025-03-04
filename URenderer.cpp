#include "URenderer.h"

class URenderer
{
private:
    struct alignas(16) FConstants
    {
        FVector3 Offset;
        float Scale;
    };

public:
    /** Renderer�� �ʱ�ȭ �մϴ�. */
    void Create(HWND hWindow)
    {
        CreateDeviceAndSwapChain(hWindow);
        CreateFrameBuffer();
        CreateRasterizerState();
    }

    /** Renderer�� ���� ��� ���ҽ��� �����մϴ�. */
    void Release()
    {
        ReleaseRasterizerState();

        // ���� Ÿ���� �ʱ�ȭ
        DeviceContext->OMSetRenderTargets(0, nullptr, nullptr);

        ReleaseFrameBuffer();
        ReleaseDeviceAndSwapChain();
    }

    void CreateShader()
    {
        /**
         * �����ϵ� ���̴��� ����Ʈ�ڵ带 ������ ���� (ID3DBlob)
         *
         * ���� �޸� ���۸� ��Ÿ���� ����
         *   - ���⼭�� shader object bytecode�� ������� ����
         * ���� �� �޼��带 �����Ѵ�.
         *   - LPVOID GetBufferPointer
         *     - ���۸� ����Ű�� void* �����͸� �����ش�.
         *   - SIZE_T GetBufferSize
         *     - ������ ũ��(����Ʈ ����)�� �����ش�
         */
        ID3DBlob* VertexShaderCSO;
        ID3DBlob* PixelShaderCSO;

        // ���̴� ������ �� ����
        D3DCompileFromFile(L"Shaders/ShaderW0.hlsl", nullptr, nullptr, "mainVS", "vs_5_0", 0, 0, &VertexShaderCSO, nullptr);
        Device->CreateVertexShader(VertexShaderCSO->GetBufferPointer(), VertexShaderCSO->GetBufferSize(), nullptr, &SimpleVertexShader);

        D3DCompileFromFile(L"Shaders/ShaderW0.hlsl", nullptr, nullptr, "mainPS", "ps_5_0", 0, 0, &PixelShaderCSO, nullptr);
        Device->CreatePixelShader(PixelShaderCSO->GetBufferPointer(), PixelShaderCSO->GetBufferSize(), nullptr, &SimplePixelShader);

        // �Է� ���̾ƿ� ���� �� ����
        D3D11_INPUT_ELEMENT_DESC Layout[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        };

        Device->CreateInputLayout(Layout, ARRAYSIZE(Layout), VertexShaderCSO->GetBufferPointer(), VertexShaderCSO->GetBufferSize(), &SimpleInputLayout);

        VertexShaderCSO->Release();
        PixelShaderCSO->Release();

        // ���� �ϳ��� ũ�⸦ ���� (����Ʈ ����)
        Stride = sizeof(FVertexSimple);
    }
    void ReleaseShader()
    {
        if (SimpleInputLayout)
        {
            SimpleInputLayout->Release();
            SimpleInputLayout = nullptr;
        }

        if (SimplePixelShader)
        {
            SimplePixelShader->Release();
            SimplePixelShader = nullptr;
        }

        if (SimpleVertexShader)
        {
            SimpleVertexShader->Release();
            SimpleVertexShader = nullptr;
        }
    }

    void CreateConstantBuffer()
    {
        D3D11_BUFFER_DESC ConstantBufferDesc = {};
        ConstantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;                        // �� ������ CPU���� ������Ʈ �ϱ� ����
        ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;             // ��� ���۷� ����
        ConstantBufferDesc.ByteWidth = sizeof(FConstants) + 0xf & 0xfffffff0;  // 16byte�� ����� �ø�
        ConstantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;            // CPU���� ���� ������ �����ϰ� ����

        Device->CreateBuffer(&ConstantBufferDesc, nullptr, &ConstantBuffer);
    }
    void ReleaseConstantBuffer()
    {
        if (ConstantBuffer)
        {
            ConstantBuffer->Release();
            ConstantBuffer = nullptr;
        }
    }

    /** ���� ü���� �� ���ۿ� ����Ʈ ���۸� ��ü�Ͽ� ȭ�鿡 ��� */
    void SwapBuffer() const
    {
        SwapChain->Present(1, 0); // SyncInterval: VSync Ȱ��ȭ ����
    }

    /** ������ ������������ �غ� �մϴ�. */
    void Prepare() const
    {
        // ȭ�� �����
        DeviceContext->ClearRenderTargetView(FrameBufferRTV, ClearColor);

        // InputAssembler�� Vertex �ؼ� ����� ����
        DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        // Rasterization�� Viewport�� ���� 
        DeviceContext->RSSetViewports(1, &ViewportInfo);
        DeviceContext->RSSetState(RasterizerState);

        /**
         * OutputMerger ����
         * ������ ������������ ���� �ܰ�ν�, ��� �׸���(���� Ÿ��)�� ��� �׸���(����)�� ����
         */
        DeviceContext->OMSetRenderTargets(1, &FrameBufferRTV, nullptr);
        DeviceContext->OMSetBlendState(nullptr, nullptr, 0xffffffff);
    }

    /** ���̴��� �غ� �մϴ�. */
    void PrepareShader() const
    {
        // �⺻ ���̴��� InputLayout�� ����
        DeviceContext->VSSetShader(SimpleVertexShader, nullptr, 0);
        DeviceContext->PSSetShader(SimplePixelShader, nullptr, 0);
        DeviceContext->IASetInputLayout(SimpleInputLayout);

        // ���ؽ� ���̴��� ��� ���۸� ����
        if (ConstantBuffer)
        {
            DeviceContext->VSSetConstantBuffers(0, 1, &ConstantBuffer);
        }
    }

    /**
     * Buffer�� �ִ� Vertex�� �׸��ϴ�.
     * @param pBuffer �������� ����� ���ؽ� ���ۿ� ���� ������
     * @param numVertices ���ؽ� ���ۿ� ����� ���ؽ��� �� ����
     */
    void RenderPrimitive(ID3D11Buffer* pBuffer, UINT numVertices) const
    {
        UINT Offset = 0;
        DeviceContext->IASetVertexBuffers(0, 1, &pBuffer, &Stride, &Offset);

        DeviceContext->Draw(numVertices, 0);
    }

    /**
     * ���� �����ͷ� Vertex Buffer�� �����մϴ�.
     * @param Vertices ���۷� ��ȯ�� ���� ������ �迭�� ������
     * @param ByteWidth ������ �� ũ�� (����Ʈ ����)
     * @return ������ ���ؽ� ���ۿ� ���� ID3D11Buffer ������, ���� �� nullptr
     *
     * @note �� �Լ��� D3D11_USAGE_IMMUTABLE �������� ���۸� �����մϴ�.
     */
    ID3D11Buffer* CreateVertexBuffer(const FVertexSimple* Vertices, UINT ByteWidth) const
    {
        D3D11_BUFFER_DESC VertexBufferDesc = {};
        VertexBufferDesc.ByteWidth = ByteWidth;
        VertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
        VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        D3D11_SUBRESOURCE_DATA VertexBufferSRD = {};
        VertexBufferSRD.pSysMem = Vertices;

        ID3D11Buffer* VertexBuffer;
        const HRESULT Result = Device->CreateBuffer(&VertexBufferDesc, &VertexBufferSRD, &VertexBuffer);
        if (FAILED(Result))
        {
            return nullptr;
        }
        return VertexBuffer;
    }

    /** Buffer�� �����մϴ�. */
    void ReleaseVertexBuffer(ID3D11Buffer* pBuffer) const
    {
        pBuffer->Release();
    }

    /** Constant Data�� ������Ʈ �մϴ�. */
    void UpdateConstant(const FVector3& Offset, float Scale) const
    {
        if (!ConstantBuffer) return;

        D3D11_MAPPED_SUBRESOURCE ConstantBufferMSR;

        // ��� ���۸� CPU �޸𸮿� ����
        // D3D11_MAP_WRITE_DISCARD�� ���� ������ �����ϰ� ���ο� �����ͷ� ����� ���� ���
        DeviceContext->Map(ConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ConstantBufferMSR);
        {
            // ���ε� �޸𸮸� FConstants ����ü�� ĳ����
            FConstants* Constants = static_cast<FConstants*>(ConstantBufferMSR.pData);
            Constants->Offset = Offset;
            Constants->Scale = Scale;
        }
        DeviceContext->Unmap(ConstantBuffer, 0);
    }

    ID3D11Device* GetDevice() const { return Device; }
    ID3D11DeviceContext* GetDeviceContext() const { return DeviceContext; }

protected:
    /** Direct3D Device �� SwapChain�� �����մϴ�. */
    void CreateDeviceAndSwapChain(HWND hWindow)
    {
        // �����ϴ� Direct3D ��� ������ ����
        D3D_FEATURE_LEVEL FeatureLevels[] = { D3D_FEATURE_LEVEL_11_0 };

        // SwapChain ����ü �ʱ�ȭ
        DXGI_SWAP_CHAIN_DESC SwapChainDesc = {};
        SwapChainDesc.BufferDesc.Width = 0;                            // â ũ�⿡ �°� �ڵ����� ����
        SwapChainDesc.BufferDesc.Height = 0;                           // â ũ�⿡ �°� �ڵ����� ����
        SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // ���� ����
        SwapChainDesc.SampleDesc.Count = 1;                            // ��Ƽ ���ø� ��Ȱ��ȭ
        SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;   // ���� Ÿ������ ����
        SwapChainDesc.BufferCount = 2;                                 // ���� ���۸�
        SwapChainDesc.OutputWindow = hWindow;                          // �������� â �ڵ�
        SwapChainDesc.Windowed = TRUE;                                 // â ���
        SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;      // ���� ���

        // Direct3D Device�� SwapChain�� ����
        D3D11CreateDeviceAndSwapChain(
            // �Է� �Ű�����
            nullptr,                                                       // ����̽��� ���� �� ����� ���� ����Ϳ� ���� ������
            D3D_DRIVER_TYPE_HARDWARE,                                      // ���� ����̹� ������ ��Ÿ���� D3D_DRIVER_TYPE ������ ��
            nullptr,                                                       // ����Ʈ���� �����Ͷ������� �����ϴ� DLL�� ���� �ڵ�
            D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG,  // ����� ��Ÿ�� ������ �����ϴ� D3D11_CREATE_DEVICE_FLAG ������ ������ ����
            FeatureLevels,                                                 // ������� ��� ������ ������ �����ϴ� D3D_FEATURE_LEVEL �迭�� ���� ������
            ARRAYSIZE(FeatureLevels),                                      // pFeatureLevels �迭�� ��� ��
            D3D11_SDK_VERSION,                                             // SDK ����. �ַ� D3D11_SDK_VERSION�� ���
            &SwapChainDesc,                                                // SwapChain ������ ���õ� DXGI_SWAP_CHAIN_DESC ����ü�� ���� ������

            // ��� �Ű�����
            &SwapChain,                                                    // ������ IDXGISwapChain �������̽��� ���� ������
            &Device,                                                       // ������ ID3D11Device �������̽��� ���� ������
            nullptr,                                                       // ���õ� ��� ������ ��Ÿ���� D3D_FEATURE_LEVEL ���� ��ȯ
            &DeviceContext                                                 // ������ ID3D11DeviceContext �������̽��� ���� ������
        );

        // ������ SwapChain�� ���� ��������
        SwapChain->GetDesc(&SwapChainDesc);

        // ����Ʈ ���� ����
        ViewportInfo = {
            0.0f, 0.0f,
            static_cast<float>(SwapChainDesc.BufferDesc.Width), static_cast<float>(SwapChainDesc.BufferDesc.Height),
            0.0f, 1.0f
        };
    }

    /** Direct3D Device �� SwapChain�� �����մϴ�.  */
    void ReleaseDeviceAndSwapChain()
    {
        if (DeviceContext)
        {
            DeviceContext->Flush(); // �����ִ� GPU ��� ����
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

    /** ������ ���۸� �����մϴ�. */
    void CreateFrameBuffer()
    {
        // ���� ü�����κ��� �� ���� �ؽ�ó ��������
        SwapChain->GetBuffer(0, IID_PPV_ARGS(&FrameBuffer));

        // ���� Ÿ�� �� ����
        D3D11_RENDER_TARGET_VIEW_DESC FrameBufferRTVDesc = {};
        FrameBufferRTVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;      // ���� ����
        FrameBufferRTVDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D; // 2D �ؽ�ó

        Device->CreateRenderTargetView(FrameBuffer, &FrameBufferRTVDesc, &FrameBufferRTV);
    }

    /** ������ ���۸� �����մϴ�. */
    void ReleaseFrameBuffer()
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

    /** �����Ͷ����� ���¸� �����մϴ�. */
    void CreateRasterizerState()
    {
        D3D11_RASTERIZER_DESC RasterizerDesc = {};
        RasterizerDesc.FillMode = D3D11_FILL_SOLID; // ä��� ���
        RasterizerDesc.CullMode = D3D11_CULL_BACK;  // �� ���̽� �ø�

        Device->CreateRasterizerState(&RasterizerDesc, &RasterizerState);
    }

    /** �����Ͷ����� ���¸� �����մϴ�. */
    void ReleaseRasterizerState()
    {
        if (RasterizerState)
        {
            RasterizerState->Release();
            RasterizerState = nullptr;
        }
    }

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
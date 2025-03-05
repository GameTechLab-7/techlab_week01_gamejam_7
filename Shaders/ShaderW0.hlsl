// ShaderW0.hlsl

/**
 * constant buffer 정의
 * register(b#)를 사용하여 버퍼 레지스터 슬롯을 지정할 수 있다.
 */
cbuffer constants : register(b0)
{
    float3 Offset;
    float Scale;
    float Radian;
    bool bIsHit;
}

struct VS_INPUT
{
    float4 position : POSITION; // Input position from vertex buffer
    float4 color : COLOR; // Input color from vertex buffer
};

struct PS_INPUT
{
    float4 position : SV_POSITION; // Transformed position to pass to the pixel shader
    float4 color : COLOR; // Color to pass to the pixel shader
};

PS_INPUT mainVS(VS_INPUT input)
{
    PS_INPUT output;

    // Pass the position directly to the pixel shader (no transformation)
    // output.position = input.position;

    float c = cos(Radian);
    float s = sin(Radian);
    
    float x = (input.position.x * c - input.position.y * s) * Scale + Offset.x;
    float y = (input.position.x * s + input.position.y * c) * Scale + Offset.y;
        
    // 상수버퍼를 통해 넘겨 받은 Scale을 곱하고 Offset을 더해서 픽셀쉐이더로 넘김
    output.position = float4(x, y, input.position.z, input.position.w);

    // Pass the color to the pixel shader
    output.color = input.color;

    return output;
}

float4 mainPS(PS_INPUT input) : SV_TARGET
{
    if (bIsHit)
    {
        return float4(1.0, 0.0, 0.0, 1.0); // 빨간색 (RGBA)
    }

    return input.color; // 원래 색상 유지
}

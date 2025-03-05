cbuffer Constants : register(b0)
{
    float3 Offset;
    float Scale;
    float Radian;
}

Texture2D ShaderTexture : register(t0);
SamplerState SampleType : register(s0);

struct VS_INPUT
{
    float4 Position : POSITION;
    float2 TexCoord : TEXCOORD0;
};

struct PS_INPUT
{
    float4 Position : SV_POSITION;
    float2 TexCoord : TEXCOORD0;
};

PS_INPUT TextureShaderVS(VS_INPUT Input)
{
    PS_INPUT Output;

    // 회전 행렬 생성
    float2x2 RotationMatrix = float2x2(
        cos(Radian), -sin(Radian),
        sin(Radian), cos(Radian)
    );

    // 회전 적용 (x, y에만 적용)
    float2 RotatedXY = mul(Input.Position.xy, RotationMatrix);

    // 크기 조절, 회전, 이동 모두 적용
    Output.Position = float4(
        RotatedXY * Scale + Offset.xy,
        Input.Position.z * Scale + Offset.z,
        Input.Position.w
    );

    Output.TexCoord = Input.TexCoord;
    return Output;
}

float4 TextureShaderPS(PS_INPUT Input) : SV_TARGET
{
    return ShaderTexture.Sample(SampleType, Input.TexCoord);
}

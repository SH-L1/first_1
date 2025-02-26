Texture2D map : register(t0);
SamplerState samp : register(s0);

cbuffer LeftRight : register(b0)
{
    int leftRight;
    int padding[3];
}

cbuffer Color : register(b1)
{
    float4 color;
}

struct VertexInput
{
    float4 pos : POSITION;
    float2 uv : UV;
};

struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

float4 PS(PixelInput input) : SV_TARGET
{
    if (leftRight == 0)
        input.uv.x *= 1;
    else
        input.uv.x *= -1;
    
    float4 result = map.Sample(samp, input.uv) + color;
    
    return result;
}
// TextureTestPixelShader.hlsl - 텍스처 로딩 확인용
Texture2D map : register(t0);
SamplerState samp : register(s0);

struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

float4 PS(PixelInput input) : SV_TARGET
{
    // 1. 텍스처 샘플링
    float4 texColor = map.Sample(samp, input.uv);
    
    // 2. 텍스처가 로딩되었는지 확인
    // 텍스처가 검은색이면 UV 색상으로 대체
    if (texColor.r + texColor.g + texColor.b < 0.1)
    {
        // 텍스처가 거의 검은색 = 로딩 실패
        return float4(1.0, 0.0, 0.0, 1.0); // 빨간색으로 표시
    }
    
    // 3. 텍스처가 흰색이면 파란색으로 표시
    if (texColor.r + texColor.g + texColor.b > 2.8)
    {
        // 텍스처가 거의 흰색 = 기본값?
        return float4(0.0, 0.0, 1.0, 1.0); // 파란색으로 표시
    }
    
    // 4. 정상적인 텍스처 색상 반환
    return texColor;
}
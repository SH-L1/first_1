float4 VS(float4 pos : POSITION) : SV_POSITION
{
    return pos;
}

// SV : System Value
// TARGET : 그릴 곳
float4 PS() : SV_TARGET
{
    // 면 색상
    return float4(0.0f, 0.0f, 1.0f, 1.0f);
}
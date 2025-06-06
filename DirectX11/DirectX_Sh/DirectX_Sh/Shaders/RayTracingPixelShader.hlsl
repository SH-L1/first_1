Texture2D map : register(t0);
SamplerState samp : register(s0);

cbuffer LeftRight : register(b0)
{
    int leftRight;
    int padding[3];
}

cbuffer Color : register(b2)
{
    float4 color;
}

cbuffer RayTracing : register(b3)
{
    float4 screenOrigin; 
    float4 lightAndShadow; 
    float4 material; 
    int objectCount;
    int padding2[3];
}

struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

float4 PS(PixelInput input) : SV_TARGET
{
    float2 texCoord = input.uv;
    if (leftRight != 0)
        texCoord.x = 1.0 - texCoord.x;
    
    float4 texColor = map.Sample(samp, texCoord);
    
    if (texColor.a < 0.5)
        discard;
    
    float2 pixelPos = input.pos.xy;
    
    float2 lightPosScreen = lightAndShadow.xy;
    lightPosScreen.y = screenOrigin.y - lightPosScreen.y;
    
    float lighting = material.x;
    
    if (objectCount > 0 && lightAndShadow.z > 0.01)
    {
        float lightIntensity = lightAndShadow.z;
        float lightRadius = lightAndShadow.w;
        
        float distance = length(lightPosScreen - pixelPos);
        
        if (distance < lightRadius)
        {
            float attenuation = 1.0 - (distance / lightRadius);
            attenuation = pow(attenuation, 2.0);
            
            lighting += material.y * lightIntensity * attenuation;
        }
    }
    
    lighting = saturate(lighting);
    
    float3 finalColor = texColor.rgb * lighting;
    
    return float4(finalColor, texColor.a);
}
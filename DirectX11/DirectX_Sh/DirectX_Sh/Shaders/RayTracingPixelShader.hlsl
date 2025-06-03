Texture2D map : register(t0);
SamplerState samp : register(s0);

struct ObjectData
{
    float2 pos;
    float2 size;
    float2 uvOffset;
    float2 uvScale;
    float reflectivity;
    int type;
    int pad0, pad1;
};

cbuffer LeftRight : register(b0)
{
    int leftRight;
    int padding[3];
}

StructuredBuffer<ObjectData> objects : register(t1);

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

bool IntersectRect2D(float2 origin, float2 dir, float2 center, float2 halfSize, out float t, out float2 normal)
{
    float2 invDir = 1.0 / (dir + float2(0.0001, 0.0001));
    float2 t1 = (center - halfSize - origin) * invDir;
    float2 t2 = (center + halfSize - origin) * invDir;
    float2 tMin = min(t1, t2), tMax = max(t1, t2);
    float tNear = max(tMin.x, tMin.y), tFar = min(tMax.x, tMax.y);
    if (tNear > 0.0 && tNear <= tFar)
    {
        t = tNear;
        normal = (tMin.x > tMin.y)
               ? float2(-sign(invDir.x), 0)
               : float2(0, -sign(invDir.y));
        return true;
    }
    return false;
}

bool IntersectCircle2D(float2 origin, float2 dir, float2 center, float radius, out float t, out float2 normal)
{
    float2 oc = origin - center;
    float a = dot(dir, dir);
    float b = 2 * dot(oc, dir);
    float c = dot(oc, oc) - radius * radius;
    float disc = b * b - 4 * a * c;
    if (disc < 0)
        return false;
    float sqrtD = sqrt(disc);
    float t0 = (-b - sqrtD) / (2 * a);
    float t1 = (-b + sqrtD) / (2 * a);
    t = (t0 > 0) ? t0 : t1;
    if (t < 0)
        return false;
    float2 hit = origin + dir * t;
    normal = normalize(hit - center);
    return true;
}

float3 TraceRay(float2 origin, float2 dir)
{
    float minT = 1e9;
    float3 finalColor = float3(0, 0, 0);
    float3 lightPos3 = float3(lightAndShadow.xy, 0);
    float lightInt = lightAndShadow.z;
    float ambient = material.x;
    float diffCoef = material.y;
    bool hitSomething = false;

    for (int i = 0; i < objectCount; ++i)
    {
        ObjectData obj = objects[i];
        float t;
        float2 n2;
        bool hit = (obj.type == 0)
                      ? IntersectRect2D(origin, dir, obj.pos, obj.size * 0.5, t, n2)
                      : IntersectCircle2D(origin, dir, obj.pos, obj.size.x * 0.5, t, n2);

        if (hit && t < minT && t > 0.001)
        {
            minT = t;
            hitSomething = true;
            float2 hit2D = origin + dir * t;
            
            float2 localUV = (hit2D - (obj.pos - obj.size * 0.5)) / obj.size;
            localUV = saturate(localUV);
            float2 texUV = obj.uvOffset + localUV * obj.uvScale;
            
            if (leftRight == 0)
                texUV.x *= 1;
            else
                texUV.x = 1.0 - texUV.x;
                
            texUV = saturate(texUV);
            
            float3 baseCol = map.Sample(samp, texUV).rgb;

            float3 N = float3(n2, 0);
            float3 L = normalize(lightPos3 - float3(hit2D, 0));
            float diff = max(dot(N, L), 0.0);

            float dist = length(lightPos3 - float3(hit2D, 0));
            float attenuation = 1.0 / (1.0 + dist * 0.01);

            finalColor = baseCol * (ambient + diffCoef * diff * lightInt * attenuation) + color.rgb;
        }
    }

    return finalColor;
}

float4 PS(PixelInput input) : SV_TARGET
{
    float2 worldPos = float2(input.pos.x, input.pos.y);
    
    float2 lightPos = lightAndShadow.xy;
    float2 rayDir = normalize(lightPos - worldPos);
    
    float3 rayColor = TraceRay(worldPos, rayDir);
    
    if (length(rayColor) < 0.01)
    {
        float2 uv = input.uv;
        if (leftRight != 0)
            uv.x = 1.0 - uv.x;
        
        float3 texColor = map.Sample(samp, uv).rgb;
        
        float dist = length(lightPos - worldPos);
        float attenuation = 1.0 / (1.0 + dist * 0.005);
        float lighting = material.x + material.y * lightAndShadow.z * attenuation;
        
        rayColor = texColor * lighting + color.rgb;
    }
    
    return float4(rayColor, 1.0);
}
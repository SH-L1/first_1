// RayTracingPixelShader.hlsl

// 레이트레이싱 매개변수
cbuffer RayTracingParams : register(b0)
{
    float2 screenSize;
    float2 origin;
    
    float2 lightPos;
    float lightIntensity;
    
    float shadowIntensity;
    float ambient;
    
    float diffuse;
    float specular;
    float shininess;
    
    int objectCount;
    int padding;
}

// 오브젝트 정보 배열
cbuffer ObjectBuffer : register(b1)
{
    struct ObjectData
    {
        float2 pos;
        float2 size;
        float3 color;
        float reflectivity;
        int type;
        int3 padding;
    } objects[16];
}

struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

// 광선 구조체
struct Ray
{
    float2 origin;
    float2 direction;
};

// 히트 정보 구조체
struct HitResult
{
    bool isHit;
    float distance;
    float2 hitPoint;
    float2 normal;
    float3 color;
    int objectIndex;
};

// 광선 생성 함수
Ray CreateRay(float2 pixelPos)
{
    Ray ray;
    ray.origin = origin;
    ray.direction = normalize(pixelPos - origin);
    return ray;
}

// 사각형과 광선의 충돌 검사
HitResult RectIntersect(Ray ray, int objectIndex)
{
    HitResult result = (HitResult)0;
    result.isHit = false;
    
    float2 rectPos = objects[objectIndex].pos;
    float2 halfSize = objects[objectIndex].size * 0.5;
    
    // 광선과 사각형 각 변 검사
    float2 rectMin = rectPos - halfSize;
    float2 rectMax = rectPos + halfSize;
    
    // x축 방향 변 검사
    float tNear = (rectMin.x - ray.origin.x) / ray.direction.x;
    float tFar = (rectMax.x - ray.origin.x) / ray.direction.x;
    
    if (tNear > tFar) { float temp = tNear; tNear = tFar; tFar = temp; }
    
    float tyNear = (rectMin.y - ray.origin.y) / ray.direction.y;
    float tyFar = (rectMax.y - ray.origin.y) / ray.direction.y;
    
    if (tyNear > tyFar) { float temp = tyNear; tyNear = tyFar; tyFar = temp; }
    
    if (tNear > tyFar || tyNear > tFar) 
        return result;
    
    float tHit = max(tNear, tyNear);
    
    if (tHit > 0)
    {
        result.isHit = true;
        result.distance = tHit;
        result.hitPoint = ray.origin + ray.direction * tHit;
        
        // 법선 벡터 계산
        if (abs(result.hitPoint.x - rectMin.x) < 0.01)
            result.normal = float2(-1, 0);
        else if (abs(result.hitPoint.x - rectMax.x) < 0.01)
            result.normal = float2(1, 0);
        else if (abs(result.hitPoint.y - rectMin.y) < 0.01)
            result.normal = float2(0, -1);
        else
            result.normal = float2(0, 1);
            
        result.color = objects[objectIndex].color;
        result.objectIndex = objectIndex;
    }
    
    return result;
}

// 원과 광선의 충돌 검사
HitResult CircleIntersect(Ray ray, int objectIndex)
{
    HitResult result = (HitResult)0;
    result.isHit = false;
    
    float2 circlePos = objects[objectIndex].pos;
    float radius = objects[objectIndex].size.x * 0.5;
    
    float2 oc = ray.origin - circlePos;
    float a = dot(ray.direction, ray.direction);
    float b = 2.0 * dot(oc, ray.direction);
    float c = dot(oc, oc) - radius * radius;
    
    float discriminant = b * b - 4 * a * c;
    
    if (discriminant < 0)
        return result;
        
    float t = (-b - sqrt(discriminant)) / (2.0 * a);
    
    if (t > 0)
    {
        result.isHit = true;
        result.distance = t;
        result.hitPoint = ray.origin + ray.direction * t;
        result.normal = normalize(result.hitPoint - circlePos);
        result.color = objects[objectIndex].color;
        result.objectIndex = objectIndex;
    }
    
    return result;
}

// 가장 가까운 충돌 오브젝트 찾기
HitResult FindClosestHit(Ray ray)
{
    HitResult closestHit = (HitResult)0;
    closestHit.isHit = false;
    closestHit.distance = 1.0e10;
    
    for (int i = 0; i < objectCount; ++i)
    {
        HitResult hit;
        
        if (objects[i].type == 0) // 사각형
            hit = RectIntersect(ray, i);
        else // 원
            hit = CircleIntersect(ray, i);
            
        if (hit.isHit && hit.distance < closestHit.distance)
        {
            closestHit = hit;
        }
    }
    
    return closestHit;
}

// 그림자 계산
bool IsInShadow(float2 point, float2 lightDirection)
{
    Ray shadowRay;
    shadowRay.origin = point + lightDirection * 0.01; // 약간 오프셋 추가
    shadowRay.direction = lightDirection;
    
    HitResult shadowHit = FindClosestHit(shadowRay);
    
    return shadowHit.isHit;
}

// 빛 계산
float3 CalculateLighting(HitResult hit)
{
    float3 finalColor = hit.color * ambient; // 환경광
    
    if (!hit.isHit)
        return float3(0, 0, 0);
        
    // 빛 방향 계산
    float2 lightDir = normalize(lightPos - hit.hitPoint);
    
    // 그림자 검사
    bool inShadow = IsInShadow(hit.hitPoint, lightDir);
    
    if (!inShadow)
    {
        // 디퓨즈 라이팅
        float NdotL = max(dot(hit.normal, lightDir), 0.0);
        float3 diffuseLight = hit.color * diffuse * NdotL;
        
        // 스페큘러 라이팅
        float2 viewDir = normalize(origin - hit.hitPoint);
        float2 halfVec = normalize(lightDir + viewDir);
        float NdotH = max(dot(hit.normal, halfVec), 0.0);
        float3 specularLight = float3(1, 1, 1) * specular * pow(NdotH, shininess);
        
        // 빛의 세기와 거리에 따른 감쇠 계산
        float dist = length(lightPos - hit.hitPoint);
        float attenuation = 1.0 / (1.0 + 0.1 * dist + 0.01 * dist * dist);
        
        finalColor += (diffuseLight + specularLight) * lightIntensity * attenuation;
    }
    else
    {
        // 그림자 영역은 환경광만 적용
        finalColor *= shadowIntensity;
    }
    
    return finalColor;
}

float4 PS(PixelInput input) : SV_TARGET
{
    // 픽셀 위치를 월드 좌표로 변환
    float2 pixelPos = float2(input.uv.x * screenSize.x, input.uv.y * screenSize.y);
    
    // 광선 생성
    Ray ray = CreateRay(pixelPos);
    
    // 충돌 계산
    HitResult hit = FindClosestHit(ray);
    
    // 라이팅 계산
    float3 color = CalculateLighting(hit);
    
    // 배경색 (히트가 없는 경우)
    if (!hit.isHit)
        color = float3(0.1, 0.1, 0.2);
    
    return float4(color, 1.0);
}

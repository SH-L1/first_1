// TextureTestPixelShader.hlsl - �ؽ�ó �ε� Ȯ�ο�
Texture2D map : register(t0);
SamplerState samp : register(s0);

struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

float4 PS(PixelInput input) : SV_TARGET
{
    // 1. �ؽ�ó ���ø�
    float4 texColor = map.Sample(samp, input.uv);
    
    // 2. �ؽ�ó�� �ε��Ǿ����� Ȯ��
    // �ؽ�ó�� �������̸� UV �������� ��ü
    if (texColor.r + texColor.g + texColor.b < 0.1)
    {
        // �ؽ�ó�� ���� ������ = �ε� ����
        return float4(1.0, 0.0, 0.0, 1.0); // ���������� ǥ��
    }
    
    // 3. �ؽ�ó�� ����̸� �Ķ������� ǥ��
    if (texColor.r + texColor.g + texColor.b > 2.8)
    {
        // �ؽ�ó�� ���� ��� = �⺻��?
        return float4(0.0, 0.0, 1.0, 1.0); // �Ķ������� ǥ��
    }
    
    // 4. �������� �ؽ�ó ���� ��ȯ
    return texColor;
}
#include "globals.hlsli"

struct VSIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float3 WorldPos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};


float4 main(VSOut In) : SV_TARGET
{
    float4 color = (float4) 0.0f;

    // 1200 1032 // 120 130
    // 1080 -> 540
    // -540 + 1200 
    color = albedoTexture.Sample(pointSampler, In.UV);

    if (animationType == 1)
    {
        float2 diff = (AtlasSize - SpriteSize) / 2.0f;
        float2 UV = (SpriteLeftTop - diff - SpriteOffset)
                + (AtlasSize * In.UV);

        if (UV.x < SpriteLeftTop.x || UV.x > SpriteLeftTop.x + SpriteSize.x
            || UV.y < SpriteLeftTop.y || UV.y > SpriteLeftTop.y + SpriteSize.y)
            discard;

        color = atlasTexture.Sample(pointSampler, UV);
    }

    float4 lightColor = float4(0.2f, 0.2f, 0.2f, 1.0f);

    for (int i = 0; i < 2; i++)
    {
        CalculateLight2D(lightColor, In.WorldPos, i);
    }

    color *= lightColor;

    if (monsterState == 1)//hit
    {
        if (color.a > 0.0f)
        {
            color = monsterColor;
        }
    }
    else if (monsterState == 2)
    {
        if (color.a > 0.0f)
        {
            color = monsterColor;
        }
    }

    if (teleportState == 1) {
        float2 textureSize = float2(AtlasSize); // �ؽ��� ũ��
        float2 center = textureSize / 2.0f; //�߽���ǥ
        float2 pixelTexCoord = In.UV * textureSize; // ���� �ȼ��� �ؽ��� ��ǥ
        float distanceToCenter = length(pixelTexCoord - center); // �߽ɰ��� �Ÿ�
        //1.4f
        // �ʷϻ����� ����
        float4 texColor = float4(0.0f, 1.0f, 0.0f, 1.0f);
        if (color.a <= 0)
            discard;
       
        // �����ڸ� �ȼ� ó��
        float edgeThreshold = teleportDeltaTime/10.f; // �����ڸ��� �ν��� �Ÿ� �Ӱ谪
        
        if (distanceToCenter >= length(center) - (teleportDeltaTime / 9.75f))
        {
        // �����ڸ� �ȼ��� ��� ���� �ʷϻ����� ����
            //color = lerp(texColor, color, distanceToCenter / length(center));
            color = float4(0.24f, 0.89f, 0.58f, 1.0f);
        }
        
        if (distanceToCenter >= length(center) - edgeThreshold)
        {
        // �����ڸ� �ȼ��� ��� ���İ��� 0���� ����
            color.a = 0.0f;
        }
    }

    if (color.a <= 0.0f)
       discard;

    return color;
}
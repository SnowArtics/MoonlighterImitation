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
        float2 textureSize = float2(AtlasSize); // 텍스쳐 크기
        float2 center = textureSize / 2.0f; //중심좌표
        float2 pixelTexCoord = In.UV * textureSize; // 현재 픽셀의 텍스쳐 좌표
        float distanceToCenter = length(pixelTexCoord - center); // 중심과의 거리
        //1.4f
        // 초록색으로 변경
        float4 texColor = float4(0.0f, 1.0f, 0.0f, 1.0f);
        if (color.a <= 0)
            discard;
       
        // 가장자리 픽셀 처리
        float edgeThreshold = teleportDeltaTime/10.f; // 가장자리로 인식할 거리 임계값
        
        if (distanceToCenter >= length(center) - (teleportDeltaTime / 9.75f))
        {
        // 가장자리 픽셀일 경우 색을 초록색으로 변신
            //color = lerp(texColor, color, distanceToCenter / length(center));
            color = float4(0.24f, 0.89f, 0.58f, 1.0f);
        }
        
        if (distanceToCenter >= length(center) - edgeThreshold)
        {
        // 가장자리 픽셀일 경우 알파값을 0으로 설정
            color.a = 0.0f;
        }
    }

    if (color.a <= 0.0f)
       discard;

    return color;
}
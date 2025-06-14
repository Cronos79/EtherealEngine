#include "ShaderTypes.hlsli"

struct VSInput
{
    float3 Position : POSITION;
    float3 Normal : NORMAL; // Optional for lighting
    float2 TexCoord : TEXCOORD; // Optional for texturing
};

struct VSOutput
{
    float4 Position : SV_POSITION;
    float3 WorldPos : TEXCOORD0;
};

VSOutput main(VSInput input)
{
    VSOutput output;

    float4 worldPosition = mul(float4(input.Position, 1.0f), World);
    float4 viewPosition = mul(worldPosition, View);
    output.Position = mul(viewPosition, Projection);

    output.WorldPos = worldPosition.xyz;
    return output;
}
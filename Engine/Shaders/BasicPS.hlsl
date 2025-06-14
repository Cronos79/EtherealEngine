struct VSOutput
{
    float4 Position : SV_POSITION;
    float3 WorldPos : TEXCOORD0;
};

float4 main(VSOutput input) : SV_Target
{
    return float4(0.0f, 0.5f, 1.0f, 1.0f); // Sky-blue color
}
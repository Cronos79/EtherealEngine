#ifndef SHADER_TYPES_H
#define SHADER_TYPES_H

cbuffer ObjectConstants : register(b0)
{
    float4x4 World;
};

cbuffer CameraConstants : register(b1)
{
    float4x4 View;
    float4x4 Projection;
};

#endif // SHADER_TYPES_H
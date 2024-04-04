cbuffer FTransform : register(b0)
{
    float4 Scale;
    float4 Rotation;
    float4 Position;
    float4x4 ScaleMat;
    float4x4 RotationMat;
    float4x4 PositionMat;
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
    float4x4 WVP;
};

cbuffer TestCheck : register(b1)
{
    float4 Test;
};
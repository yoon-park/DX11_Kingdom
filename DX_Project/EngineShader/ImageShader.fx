#include "EngineShaderBase.hlsli"

struct ImageVSOutPut
{
    float4 POSITION : SV_POSITION;
};

ImageVSOutPut ImageShader_VS(FEngineVertex _Input)
{
    ImageVSOutPut Out = (ImageVSOutPut) 0;
    Out.POSITION = _Input.POSITION;
    Out.POSITION = mul(_Input.POSITION, WVP);
    Out.POSITION.x = Test.x;
    
    return Out;
}

struct ImagePSOutPut
{
    float4 COLOR : SV_Target0;
};

cbuffer OutPutColor : register(b0)
{
    float4 Color;
};

ImagePSOutPut ImageShader_PS(ImageVSOutPut _Input)
{
    ImagePSOutPut Out = (ImagePSOutPut) 0;
    Out.COLOR = float4(1.0f, 0.0f, 0.0f, 1.0f);
    
    return Out;
}
#include "EngineShaderBase.hlsli"

cbuffer OutPutColor : register(b0)
{
    float4 Color;
};

struct ImageVSOutPut
{
    float4 POSITION : SV_POSITION;
};

ImageVSOutPut ColorShader_VS(FEngineVertex _Input)
{
    ImageVSOutPut Out = (ImageVSOutPut) 0;
    Out.POSITION = _Input.POSITION;
    Out.POSITION = mul(_Input.POSITION, WVP);
    
    return Out;
}

struct ImagePSOutPut
{
    float4 COLOR : SV_Target0;
};


ImagePSOutPut ColorShader_PS(ImageVSOutPut _Input)
{
    ImagePSOutPut Out = (ImagePSOutPut) 0;
    Out.COLOR = float4(1.0f, 0.0f, 0.0f, 1.0f);

    return Out;
}
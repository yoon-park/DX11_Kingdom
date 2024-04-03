#include "EngineVertex.hlsli"

struct ImageVSOutPut
{
    float4 POSITION : SV_POSITION;
};

ImageVSOutPut ImageShader_VS(FEngineVertex _Input)
{
    ImageVSOutPut Out = (ImageVSOutPut) 0;
    Out.POSITION = _Input.POSITION;
    return Out;
}

struct ImagePSOutPut
{
    float4 COLOR : SV_Target0;
};

ImagePSOutPut ImageShader_PS(ImageVSOutPut _Input)
{
    ImagePSOutPut Out = (ImagePSOutPut) 0;
    Out.COLOR = float4(1.0f, 0.0f, 0.0f, 1.0f);
    return Out;
}
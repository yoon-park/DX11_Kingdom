#include "EngineShaderBase.hlsli"

struct ImageVSOutPut
{
    float4 POSITION : SV_POSITION;
};

ImageVSOutPut ImageShader_VS(FEngineVertex _Input)
{
    ImageVSOutPut Out = (ImageVSOutPut) 0;
    Out.POSITION = mul(_Input.POSITION, WVP);
    
    return Out;
}

struct ImagePSOutPut
{
    float4 COLOR : SV_Target0;
};

Texture2D Image : register(t0);
SamplerState Sampler : register(s0);

ImagePSOutPut ImageShader_PS(ImageVSOutPut _Input)
{
    ImagePSOutPut Out = (ImagePSOutPut) 0;
    Out.COLOR = Image.Sample(Sampler, float2(0.0f, 0.0f));
    
    return Out;
}
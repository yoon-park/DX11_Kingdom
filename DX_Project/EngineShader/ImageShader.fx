#include "EngineShaderBase.hlsli"

struct ImageVSOutPut
{
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};

ImageVSOutPut ImageShader_VS(FEngineVertex _Input)
{
    ImageVSOutPut Out = (ImageVSOutPut) 0;
    
    Out.POSITION = mul(_Input.POSITION, WVP);
    Out.TEXCOORD = _Input.TEXCOORD;
    
    return Out;
}

struct ImagePSOutPut
{
    float4 COLOR : SV_Target0;
};

Texture2D Image : register(t0);
SamplerState Image_Sampler : register(s0);

ImagePSOutPut ImageShader_PS(ImageVSOutPut _Input)
{
    ImagePSOutPut Out = (ImagePSOutPut) 0;
    
    Out.COLOR = Sampling(Image, _Input.TEXCOORD);
    
    return Out;
}
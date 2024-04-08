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

TextureSet(Image, 0)

cbuffer ResultColorValue : register(b10)
{
    float4 PlusColor;
};

ImagePSOutPut ImageShader_PS(ImageVSOutPut _Input)
{
    ImagePSOutPut Out = (ImagePSOutPut) 0;
    
    Out.COLOR = Sampling(Image, _Input.TEXCOORD);
    Out.COLOR.xyz += PlusColor.xyz;
    
    return Out;
}
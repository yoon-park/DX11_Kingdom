#include "PreCompile.h"
#include "EngineRenderTarget.h"

#include "EngineCore.h"
#include "EngineTexture.h"

UEngineRenderTarget::UEngineRenderTarget()
{

}

UEngineRenderTarget::~UEngineRenderTarget()
{

}


void UEngineRenderTarget::AddNewTexture(std::shared_ptr<UEngineTexture> _Texture, const float4& _Color)
{
	Textures.push_back(_Texture);
	RTVs.push_back(_Texture->GetRTV());
	ClearColors.push_back(_Color);
}


void UEngineRenderTarget::Clear()
{
	for (size_t i = 0; i < RTVs.size(); i++)
	{
		GEngine->GetDirectXContext()->ClearRenderTargetView(RTVs[i], ClearColors[i].Arr1D);
	}
}
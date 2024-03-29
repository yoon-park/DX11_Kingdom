#include "PreCompile.h"
#include "EngineTexture.h"

#include "EngineCore.h"

UEngineTexture::UEngineTexture()
{

}

UEngineTexture::~UEngineTexture()
{
	if (RTV != nullptr)
	{
		RTV->Release();
	}

	if (Texture2D != nullptr)
	{
		Texture2D->Release();
	}
}

void UEngineTexture::CreateRes(ID3D11Texture2D* _Texture)
{
	Texture2D = _Texture;

	Texture2D->GetDesc(&Desc);

	CreateRenderTargetView();
}

void UEngineTexture::CreateRenderTargetView()
{
	if (RTV != nullptr)
	{
		return;
	}

	if (Texture2D == nullptr)
	{
		MsgBoxAssert("생성되지 않은 텍스처로 렌더타겟뷰를 생성하려 했습니다.");
		return;
	}

	HRESULT Result = GEngine->GetDirectXDevice()->CreateRenderTargetView(Texture2D, nullptr, &RTV);

	if (Result != S_OK)
	{
		MsgBoxAssert("렌더타겟뷰 생성에 실패했습니다.");
		return;
	}
}
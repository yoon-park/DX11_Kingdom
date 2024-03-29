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
		MsgBoxAssert("�������� ���� �ؽ�ó�� ����Ÿ�ٺ並 �����Ϸ� �߽��ϴ�.");
		return;
	}

	HRESULT Result = GEngine->GetDirectXDevice()->CreateRenderTargetView(Texture2D, nullptr, &RTV);

	if (Result != S_OK)
	{
		MsgBoxAssert("����Ÿ�ٺ� ������ �����߽��ϴ�.");
		return;
	}
}
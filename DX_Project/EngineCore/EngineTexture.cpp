#include "PreCompile.h"
#include "EngineTexture.h"

#include "EngineCore.h"

#pragma comment (lib, "DirectXTex.lib")

UEngineTexture::UEngineTexture()
{

}

UEngineTexture::~UEngineTexture()
{
	if (SRV != nullptr)
	{
		SRV->Release();
	}

	if (RTV != nullptr)
	{
		RTV->Release();
	}

	if (Texture2D != nullptr)
	{
		Texture2D->Release();
	}
}

void UEngineTexture::ResCreate(ID3D11Texture2D* _Texture)
{
	Texture2D = _Texture;

	Texture2D->GetDesc(&Desc);

	CreateRenderTargetView();
}

void UEngineTexture::ResLoad()
{
	UEnginePath File = GetEnginePath();
	std::string Ext = UEngineString::ToUpper(File.GetExtension());
	std::wstring wPath = UEngineString::AnsiToUniCode(File.GetFullPath());

	if (Ext == ".DDS")
	{
		if (DirectX::LoadFromDDSFile(wPath.c_str(), DirectX::DDS_FLAGS_NONE, &Data, Image) != S_OK)
		{
			MsgBoxAssert("DDS ���Ϸε忡 �����߽��ϴ�.");
		};
	}
	else if (Ext == ".TGA")
	{
		if (DirectX::LoadFromTGAFile(wPath.c_str(), DirectX::TGA_FLAGS_NONE, &Data, Image) != S_OK)
		{
			MsgBoxAssert("TGA ���Ϸε忡 �����߽��ϴ�.");
		};
	}
	else
	{
		if (DirectX::LoadFromWICFile(wPath.c_str(), DirectX::WIC_FLAGS_NONE, &Data, Image) != S_OK)
		{
			MsgBoxAssert("PNG ���Ϸε忡 �����߽��ϴ�.");
		};
	}

	if (DirectX::CreateShaderResourceView(
		GEngine->GetDirectXDevice(),
		Image.GetImages(),
		Image.GetImageCount(),
		Image.GetMetadata(),
		&SRV) != S_OK
	)
	{
		MsgBoxAssert("�ؽ�ó ���̴� ���� ���� ������ �����߽��ϴ�. : " + GetName());
		return;
	}

	Desc.Width = static_cast<UINT>(Data.width);
	Desc.Height = static_cast<UINT>(Data.height);
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

void UEngineTexture::Setting(EShaderType _Type, UINT _Slot)
{
	switch (_Type)
	{
	case EShaderType::Vertex:
		GEngine->GetDirectXContext()->VSSetShaderResources(_Slot, 1, &SRV);
		break;
	case EShaderType::Pixel:
		GEngine->GetDirectXContext()->PSSetShaderResources(_Slot, 1, &SRV);
		break;
	case EShaderType::NONE:
	default:
		MsgBoxAssert("Ÿ���� �Һи��� �ؽ�ó �����Դϴ�.");
		break;
	}
}

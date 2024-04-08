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
			MsgBoxAssert("DDS 파일로드에 실패했습니다.");
		};
	}
	else if (Ext == ".TGA")
	{
		if (DirectX::LoadFromTGAFile(wPath.c_str(), DirectX::TGA_FLAGS_NONE, &Data, Image) != S_OK)
		{
			MsgBoxAssert("TGA 파일로드에 실패했습니다.");
		};
	}
	else
	{
		if (DirectX::LoadFromWICFile(wPath.c_str(), DirectX::WIC_FLAGS_NONE, &Data, Image) != S_OK)
		{
			MsgBoxAssert("PNG 파일로드에 실패했습니다.");
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
		MsgBoxAssert("텍스처 쉐이더 세팅 권한 생성에 실패했습니다. : " + GetName());
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
		MsgBoxAssert("타입이 불분명한 텍스처 세팅입니다.");
		break;
	}
}

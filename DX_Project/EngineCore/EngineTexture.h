#pragma once

class UEngineTexture : public UEngineResources<UEngineTexture>
{
public:
	UEngineTexture();
	~UEngineTexture();

	UEngineTexture(const UEngineTexture& _Other) = delete;
	UEngineTexture(UEngineTexture&& _Other) noexcept = delete;
	UEngineTexture& operator=(const UEngineTexture& _Other) = delete;
	UEngineTexture& operator=(UEngineTexture&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineTexture> Create(ID3D11Texture2D* _Texture)
	{
		std::shared_ptr<UEngineTexture> NewRes = CreateResUnName();
		NewRes->CreateRes(_Texture);
		return NewRes;
	}

	ID3D11RenderTargetView* GetRTV()
	{
		return RTV;
	}

protected:

private:
	ID3D11Texture2D* Texture2D = nullptr;
	ID3D11RenderTargetView* RTV = nullptr;
	D3D11_TEXTURE2D_DESC Desc;

	void CreateRes(ID3D11Texture2D* _Texture);
	void CreateRenderTargetView();
};
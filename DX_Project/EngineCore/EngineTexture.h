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
		NewRes->Texture = _Texture;
		return NewRes;
	}

protected:

private:
	ID3D11Texture2D* Texture = nullptr;
};
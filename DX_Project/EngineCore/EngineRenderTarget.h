#pragma once

class UEngineTexture;

class UEngineRenderTarget : public UEngineResources<UEngineRenderTarget>
{
public:
	UEngineRenderTarget();
	~UEngineRenderTarget();

	UEngineRenderTarget(const UEngineRenderTarget& _Other) = delete;
	UEngineRenderTarget(UEngineRenderTarget&& _Other) noexcept = delete;
	UEngineRenderTarget& operator=(const UEngineRenderTarget& _Other) = delete;
	UEngineRenderTarget& operator=(UEngineRenderTarget&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineRenderTarget> Create(std::shared_ptr<UEngineTexture> _Texture)
	{
		std::shared_ptr<UEngineRenderTarget> NewRes = CreateResUnName();
		NewRes->AddNewTexture(_Texture);
		return NewRes;
	}

protected:

private:
	std::vector<std::shared_ptr<UEngineTexture>> Textures;

	void AddNewTexture(std::shared_ptr<UEngineTexture> _Texture);
};
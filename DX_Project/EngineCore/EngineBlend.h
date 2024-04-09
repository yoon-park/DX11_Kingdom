#pragma once
#include <EnginePlatform/EngineResources.h>

class UEngineMaterial;

class UEngineBlend : public UEngineResources<UEngineBlend>
{
	friend UEngineMaterial;

public:
	UEngineBlend();
	~UEngineBlend();

	UEngineBlend(const UEngineBlend& _Other) = delete;
	UEngineBlend(UEngineBlend&& _Other) noexcept = delete;
	UEngineBlend& operator=(const UEngineBlend& _Other) = delete;
	UEngineBlend& operator=(UEngineBlend&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineBlend> Create(
		std::string_view _Name, 
		const D3D11_BLEND_DESC& _Info)
	{
		std::shared_ptr<UEngineBlend> Res = CreateResName(_Name);
		Res->ResCreate(_Info);
		return Res;
	}

protected:


private:
	ID3D11BlendState* State = nullptr;
	float4 Factor = float4::Zero;
	UINT Mask = 0xFFFFFFFF;

	void ResCreate(const D3D11_BLEND_DESC& _Info);
	void Setting();
};
#pragma once
#include "EngineTexture.h"

class UEngineTexture;

struct FSpriteInfo
{
	FVector CuttingPosition = FVector::Zero;
	FVector CuttingSize = FVector::One;
	std::shared_ptr<UEngineTexture> Texture = nullptr;
};

class UEngineSprite : public UEngineResources<UEngineSprite>
{
public:
	UEngineSprite();
	~UEngineSprite();

	UEngineSprite(const UEngineSprite& _Other) = delete;
	UEngineSprite(UEngineSprite&& _Other) noexcept = delete;
	UEngineSprite& operator=(const UEngineSprite& _Other) = delete;
	UEngineSprite& operator=(UEngineSprite&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineSprite> Load(std::string_view _Path)
	{
		UEnginePath NewPath = UEnginePath(std::filesystem::path(_Path));
		std::string FileName = NewPath.GetFileName();
		return Load(_Path, FileName);
	}

	static std::shared_ptr<UEngineSprite> Load(std::string_view _Path, std::string_view _Name)
	{
		std::shared_ptr<UEngineSprite> NewRes = CreateResName(_Path, _Name);
		NewRes->ResLoad();
		return NewRes;
	}

	static std::shared_ptr<UEngineSprite> LoadFolder(std::string_view _Path)
	{
		UEnginePath NewPath = UEnginePath(std::filesystem::path(_Path));
		std::string FileName = NewPath.GetFileName();

		std::shared_ptr<UEngineSprite> NewRes = CreateResName(_Path, FileName);
		NewRes->ResLoadFolder();
		return NewRes;
	}

	static std::shared_ptr<UEngineSprite> CreateCutting(std::string_view _Path)
	{
		UEnginePath NewPath = UEnginePath(std::filesystem::path(_Path));
		std::string FileName = NewPath.GetFileName();

		std::shared_ptr<UEngineSprite> NewRes = CreateResName(_Path, FileName);
		NewRes->ResLoadFolder();
		return NewRes;
	}

	FSpriteInfo GetSpriteInfo(UINT _Index)
	{
		return Infos[_Index];
	}

protected:

private:
	std::vector<FSpriteInfo> Infos;

	void ResLoad();
	void ResLoadFolder();
};
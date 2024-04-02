#pragma once

template<typename ResType>
class UEngineResources : public UPathObject
{
public:
	UEngineResources() {}
	~UEngineResources() {}

	UEngineResources(const UEngineResources& _Other) = delete;
	UEngineResources(UEngineResources&& _Other) noexcept = delete;
	UEngineResources& operator=(const UEngineResources& _Other) = delete;
	UEngineResources& operator=(UEngineResources&& _Other) noexcept = delete;

	static bool IsRes(std::string_view _Name)
	{
		std::string UpperName = UEngineString::ToUpper(_Name);
		return NameResources.contains(UpperName);
	}

	static std::shared_ptr<ResType> FindRes(std::string_view _Name)
	{
		std::string UpperName = UEngineString::ToUpper(_Name);

		if (NameResources.contains(UpperName) == false)
		{
			return nullptr;
		}

		return NameResources[UpperName];
	}

	static std::shared_ptr<ResType> CreateResName(std::string_view _Path)
	{
		UEnginePath NewPath = UEnginePath(std::filesystem::path(_Path));
		std::string FileName = NewPath.GetFileName();
		
		return CreateResName(FileName, _Path);
	}

	static std::shared_ptr<ResType> CreateResName(std::string_view _Name, std::string_view _Path)
	{
		std::string UpperName = UEngineString::ToUpper(_Name);

		std::shared_ptr<ResType> NewRes = std::make_shared<ResType>();
		NewRes->SetName(_Name);
		NewRes->SetPath(_Path);

		if (NameResources.contains(UpperName) == true)
		{
			MsgBoxAssert("같은 이름의 리소스가 이미 존재합니다. : " + UpperName);
		}

		NameResources[UpperName] = NewRes;
		return NewRes;
	}

	static std::shared_ptr<ResType> CreateResUnName()
	{
		std::shared_ptr<ResType> NewRes = std::make_shared<ResType>();
		UnNameResources.push_back(NewRes);

		return NewRes;
	}

	static void ResourcesRelease()
	{
		UnNameResources.clear();
		NameResources.clear();
	}

protected:

private:
	static std::map<std::string, std::shared_ptr<ResType>> NameResources;
	static std::list<std::shared_ptr<ResType>> UnNameResources;
};

template<typename ResType>
std::map<std::string, std::shared_ptr<ResType>> UEngineResources<ResType>::NameResources;

template<typename ResType>
std::list<std::shared_ptr<ResType>> UEngineResources<ResType>::UnNameResources;
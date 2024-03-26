#pragma once
#include "EnginePath.h"
#include "NameObject.h"

class UPathObject : public UNameObject
{
public:
	UPathObject();
	~UPathObject();

	UPathObject(const UPathObject& _Other) = delete;
	UPathObject(UPathObject&& _Other) noexcept = delete;
	UPathObject& operator=(const UPathObject& _Other) = delete;
	UPathObject& operator=(UPathObject&& _Other) noexcept = delete;

	std::string GetPath()
	{
		return Path;
	}

	UEnginePath GetEnginePath()
	{
		return UEnginePath(std::filesystem::path(Path));
	}

	void SetPath(std::string_view _View)
	{
		Path = _View;
	}

protected:

private:
	std::string Path;
};


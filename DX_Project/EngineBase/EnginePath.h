#pragma once
#include <string>
#include <filesystem>

class UEnginePath
{
public:
	UEnginePath();
	UEnginePath(std::filesystem::path _Path);
	~UEnginePath();

	/*
	UEnginePath(const UEnginePath& _Other) = delete;
	UEnginePath(UEnginePath&& _Other) noexcept = delete;
	UEnginePath& operator=(const UEnginePath& _Other) = delete;
	UEnginePath& operator=(UEnginePath&& _Other) noexcept = delete;
	*/

	std::string GetFullPath() const
	{
		return Path.string();
	}

	std::string GetFileName() const;
	std::string GetExtension() const;

	bool IsFile();
	bool IsDirectory();
	bool IsRoot();
	bool IsExists();

	void Move(std::string_view _Path);
	void MoveParent();

	std::string AppendPath(std::string_view _Path);

protected:
	std::filesystem::path Path;

private:

};


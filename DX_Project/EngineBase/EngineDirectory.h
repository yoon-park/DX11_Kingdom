#pragma once
#include "EnginePath.h"

class UEngineFile;

class UEngineDirectory : public UEnginePath
{
public:
	UEngineDirectory();
	UEngineDirectory(const UEnginePath& _Path);
	~UEngineDirectory();
	
	/*
	UEngineDirectory(const UEngineDirectory& _Other) = delete;
	UEngineDirectory(UEngineDirectory&& _Other) noexcept = delete;
	UEngineDirectory& operator=(const UEngineDirectory& _Other) = delete;
	UEngineDirectory& operator=(UEngineDirectory&& _Other) noexcept = delete;
	*/

	bool IsFile(std::string_view _FileName);
	UEngineFile GetPathFromFile(std::string_view FileName);

	std::string GetFolderName() const
	{
		return GetFileName();
	}

	std::vector<UEngineDirectory> GetAllDirectory(bool _Recursive = false);
	std::vector<UEngineFile> GetAllFile(std::vector<std::string> _Ext = std::vector<std::string>(), bool _Recursive = false);

	void MoveToSearchChild(std::string_view _Path);

protected:

private:
	void AllDirectoryRecursive(const std::string_view _Path, std::vector<UEngineDirectory>& _Result, bool _Recursive = false);
	void AllFileRecursive(const std::string_view _Path, std::vector<UEngineFile>& _Result, std::vector<std::string> _Ext = std::vector<std::string>(), bool _Recursive = false);
};


#include "PreCompile.h"
#include "EngineDirectory.h"

#include "EngineDebug.h"
#include "EngineString.h"
#include "EngineFile.h"

UEngineDirectory::UEngineDirectory() 
{

}

UEngineDirectory::UEngineDirectory(const UEnginePath& _Path)
	: UEnginePath(_Path.GetFullPath())
{

}

UEngineDirectory::~UEngineDirectory() 
{

}

bool UEngineDirectory::IsFile(std::string_view _FileName)
{
	std::filesystem::path FilePath = GetFullPath() + "\\" + _FileName.data();
	return std::filesystem::exists(FilePath);
}

UEngineFile UEngineDirectory::GetPathFromFile(std::string_view FileName)
{
	std::string NewFilePath = GetFullPath() + "\\" + FileName.data();
	return std::filesystem::path(NewFilePath);
}

void UEngineDirectory::MoveToSearchChild(std::string_view _Path)
{
	while (true)
	{
		std::vector<UEngineDirectory> Dir = GetAllDirectory();

		for (UEngineDirectory& _Dir : Dir)
		{
			std::string UpperLeft = UEngineString::ToUpper(_Dir.GetFileName());
			std::string UpperRight = UEngineString::ToUpper(_Path);

			if (UpperLeft == UpperRight)
			{
				Move(_Path);
				return;
			}
		}

		if (IsRoot())
		{
			MsgBoxAssert("��Ʈ ���丮���� �˻�������, �������� �ʴ� ����Դϴ�. : " + std::string(_Path));
		}

		MoveParent();
	}
}

std::vector<UEngineDirectory> UEngineDirectory::GetAllDirectory(bool _Recursive)
{
	std::vector<UEngineDirectory> Result;
	AllDirectoryRecursive(Path.string(), Result, _Recursive);
	return Result;
}

std::vector<UEngineFile> UEngineDirectory::GetAllFile(
	std::vector<std::string> _Ext,
	bool _Rescursive
)
{
	std::vector<UEngineFile> Result;

	for (size_t i = 0; i < _Ext.size(); i++)
	{
		_Ext[i] = UEngineString::ToUpper(_Ext[i]);
	}

	AllFileRecursive(Path.string(), Result, _Ext, _Rescursive);
	return Result;
}

void UEngineDirectory::AllDirectoryRecursive(const std::string_view _Path, std::vector<UEngineDirectory>& _Result, bool _Recursive/* = false*/)
{
	std::filesystem::directory_iterator DirIter = std::filesystem::directory_iterator(_Path);

	for (const std::filesystem::directory_entry& Entry : DirIter)
	{
		std::filesystem::path Path = Entry.path();
		std::filesystem::path Ext = Entry.path().extension();
		std::string UpperExt = UEngineString::ToUpper(Ext.string());

		if (Entry.is_directory() != true)
		{
			continue;
		}

		_Result.push_back(UEngineDirectory(Path));

		if (_Recursive == true)
		{
			AllDirectoryRecursive(Path.string(), _Result, _Recursive);
		}
	}
}

void UEngineDirectory::AllFileRecursive(
	const std::string_view _Path,
	std::vector<UEngineFile>& _Result,
	std::vector<std::string> _Ext,
	bool _Recursive)
{
	std::filesystem::directory_iterator DirIter = std::filesystem::directory_iterator(_Path);

	for (const std::filesystem::directory_entry& Entry : DirIter)
	{
		std::filesystem::path Path = Entry.path();
		std::filesystem::path Ext = Entry.path().extension();
		std::string UpperExt = UEngineString::ToUpper(Ext.string());

		if (Entry.is_directory() == true)
		{
			if (_Recursive == true)
			{
				AllFileRecursive(Path.string(), _Result, _Ext, _Recursive);
			}
			continue;
		}

		if (_Ext.size() == 0)
		{
			_Result.push_back(UEngineFile(Path.string()));
			continue;
		}

		bool Check = false;

		for (size_t i = 0; i < _Ext.size(); i++)
		{
			if (_Ext[i] == UpperExt)
			{
				Check = true;
			}
		}

		if (Check == true)
		{
			_Result.push_back(UEngineFile(Path.string()));
		}
	}
}
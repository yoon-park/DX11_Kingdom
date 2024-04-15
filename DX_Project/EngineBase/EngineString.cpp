#include "PreCompile.h"
#include "EngineString.h"

#include "EngineDebug.h"

UEngineString::UEngineString() 
{

}

UEngineString::~UEngineString() 
{

}

std::string UEngineString::ToUpper(std::string_view View)
{
	std::string Name = View.data();

	for (char& _Ch : Name)
	{
		_Ch = std::toupper(_Ch);
	}

	return Name;
}

std::wstring UEngineString::AnsiToUniCode(std::string_view _View)
{
	int Size = MultiByteToWideChar(CP_ACP, 0, _View.data(), static_cast<int>(_View.size()), nullptr, 0);

	if (Size == 0)
	{
		MsgBoxAssert("문자열 변환에 실패했거나, 크기가 0인 문자열을 변환하려 했습니다.");
		return L"";
	}

	std::wstring Result;
	Result.resize(Size);

	Size = MultiByteToWideChar(CP_ACP, 0, _View.data(), static_cast<int>(_View.size()), &Result[0], Size);

	if (Size == 0)
	{
		MsgBoxAssert("문자열 변환에 실패했거나, 크기가 0인 문자열을 변환하려 했습니다.");
		return L"";
	}

	return Result;
}

std::vector<std::string> UEngineString::StringCutting(std::string& _Value, std::string_view _Start, std::string_view _End)
{
	std::vector<std::string> Result;

	size_t StartFindOffset = 0;

	while (true)
	{
		StartFindOffset = _Value.find_first_of(_Start, StartFindOffset);

		if (StartFindOffset == std::string::npos)
		{
			break;
		}

		size_t EndFindOffset = _Value.find_first_of(_End, StartFindOffset);

		if (EndFindOffset == std::string::npos)
		{
			break;
		}

		std::string ParseString = _Value.substr(StartFindOffset + 1, EndFindOffset - StartFindOffset - 1);
		Result.push_back(ParseString);
		StartFindOffset = EndFindOffset;
	}

	return Result;
}
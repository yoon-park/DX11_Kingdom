#include "EngineString.h"

#include <Windows.h>

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
		MsgBoxAssert("문자열 변환에 실패했거나, 크기가 0인 문자열을 변환시키려 했습니다.");
		return L"";
	}

	std::wstring Result;
	Result.resize(Size);

	Size = MultiByteToWideChar(CP_ACP, 0, _View.data(), static_cast<int>(_View.size()), &Result[0], Size);

	if (Size == 0)
	{
		MsgBoxAssert("문자열 변환에 실패했거나, 크기가 0인 문자열을 변환시키려 했습니다.");
		return L"";
	}

	return Result;
}
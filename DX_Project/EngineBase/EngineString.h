#pragma once
#include <string>
#include <string_view>
#include <vector>

class UEngineString
{
public:
	static std::string ToUpper(std::string_view View);
	static std::wstring AnsiToUniCode(std::string_view View);
	static std::vector<std::string> StringCutting(std::string& _Value, std::string_view _Start, std::string_view _End);

protected:

private:
	UEngineString();
	~UEngineString();

	UEngineString(const UEngineString& _Other) = delete;
	UEngineString(UEngineString&& _Other) noexcept = delete;
	UEngineString& operator=(const UEngineString& _Other) = delete;
	UEngineString& operator=(UEngineString&& _Other) noexcept = delete;
};


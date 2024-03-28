#pragma once

struct FEngineOption : public UEngineSerializeObject
{
public:
	std::string WindowTitle = "Title";
	FVector WindowScale = { 1280.0f, 720.0f };
	bool IsDebug = false;

	void Serialize(UEngineSerializer& _Ser) override
	{
		{
			std::string DebugOptionText;

			DebugOptionText += std::format("WindowTitle : [{}]\n", WindowTitle);
			DebugOptionText += std::format("WindowScale : [{}], [{}]\n", WindowScale.iX(), WindowScale.iY());
			DebugOptionText += std::format("IsDebug : [{}]\n", IsDebug);

			_Ser.WriteText(DebugOptionText);
		}
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		std::string OptionText = _Ser.ToString();

		std::vector<std::string> Values = UEngineString::StringCutting(OptionText, "[", "]");

		WindowTitle = Values[0];

		WindowScale.X = static_cast<float>(std::atof(Values[1].c_str()));
		WindowScale.Y = static_cast<float>(std::atof(Values[2].c_str()));

		std::string IsDebugUpper = UEngineString::ToUpper(Values[3]);

		if (IsDebugUpper == "FALSE")
		{
			IsDebug = false;
		}
		else if (IsDebugUpper == "TRUE")
		{
			IsDebug = true;
		}
		else
		{
			MsgBoxAssert("IsDebug 옵션이 이상한 글자로 채워져 있습니다.");
		}
	}
};
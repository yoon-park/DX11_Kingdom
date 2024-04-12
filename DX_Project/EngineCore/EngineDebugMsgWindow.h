#pragma once
#include "EngineDefines.h"
#include "EngineEditorWindow.h"

class UEngineDebugMsgWindow : public UEngineEditorWindow
{
	GENERATED_BODY(UEngineEditorWindow);

public:
	UEngineDebugMsgWindow();
	~UEngineDebugMsgWindow();

	UEngineDebugMsgWindow(const UEngineDebugMsgWindow& _Other) = delete;
	UEngineDebugMsgWindow(UEngineDebugMsgWindow&& _Other) noexcept = delete;
	UEngineDebugMsgWindow& operator=(const UEngineDebugMsgWindow& _Other) = delete;
	UEngineDebugMsgWindow& operator=(UEngineDebugMsgWindow&& _Other) noexcept = delete;

	static void PushMsg(std::string_view _Msg);

protected:
	void Init() override;
	void OnGui(float _Delta) override;

private:
	static std::vector<std::string> Msg;
};
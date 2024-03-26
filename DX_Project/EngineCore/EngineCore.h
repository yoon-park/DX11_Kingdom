#pragma once
#include <Windows.h>

#include <EnginePlatform/EngineWindow.h>

#pragma comment (lib, "EngineBase.lib")
#pragma comment (lib, "EnginePlatform.lib")

class UEngineCore
{
public:
	UEngineCore();
	~UEngineCore();

	UEngineCore(const UEngineCore& _Other) = delete;
	UEngineCore(UEngineCore&& _Other) noexcept = delete;
	UEngineCore& operator=(const UEngineCore& _Other) = delete;
	UEngineCore& operator=(UEngineCore&& _Other) noexcept = delete;

	static void SetWindowScale(FVector _Scale)
	{
		EngineWindow.SetWindowScale(_Scale);
	}

	static void Start(HINSTANCE _Inst);

protected:

private:
	static UEngineWindow EngineWindow;
};
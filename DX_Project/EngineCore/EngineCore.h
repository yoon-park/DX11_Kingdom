#pragma once
#include <Windows.h>

#include <EnginePlatform/EngineWindow.h>
#include "EngineOption.h"
#include "EngineGraphicDevice.h"

#pragma comment (lib, "EngineBase.lib")
#pragma comment (lib, "EnginePlatform.lib")

class UserCore
{
public:
	virtual void Initialize() = 0;
};

class UEngineCore
{
public:
	UEngineCore();
	~UEngineCore();

	UEngineCore(const UEngineCore& _Other) = delete;
	UEngineCore(UEngineCore&& _Other) noexcept = delete;
	UEngineCore& operator=(const UEngineCore& _Other) = delete;
	UEngineCore& operator=(UEngineCore&& _Other) noexcept = delete;

	template<typename UserCoreType>
	static void Start(HINSTANCE _Inst)
	{
		UEngineCore Core;
		UserCoreType UserCore;
		Core.UserCorePtr = &UserCore;
		Core.EngineStart(_Inst);
	}

	void SetWindowScale(FVector _Scale)
	{
		EngineWindow.SetWindowScale(_Scale);
	}

protected:

private:
	FEngineOption EngineOption;
	UEngineTime MainTimer;
	UEngineWindow EngineWindow;
	UEngineGraphicDevice EngineDevice;

	UserCore* UserCorePtr = nullptr;

	void EngineOptionInit();

	void EngineStart(HINSTANCE _Inst);
	void EngineUpdate();
};

extern UEngineCore* GEngine;
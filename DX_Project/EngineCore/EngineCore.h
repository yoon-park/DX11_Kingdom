#pragma once
#include "EngineOption.h"
#include "EngineGraphicDevice.h"

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

	UEngineGraphicDevice& GetEngineDevice()
	{
		return EngineDevice;
	}

	struct ID3D11Device* GetDirectXDevice()
	{
		return EngineDevice.GetDevice();
	}

	struct ID3D11DeviceContext* GetDirectXContext()
	{
		return EngineDevice.GetContext();
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
	void EngineEnd();
};

extern UEngineCore* GEngine;
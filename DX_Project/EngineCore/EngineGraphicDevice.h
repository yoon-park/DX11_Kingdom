#pragma once

class UEngineWindow;

class UEngineGraphicDevice
{
public:
	UEngineGraphicDevice();
	~UEngineGraphicDevice();

	UEngineGraphicDevice(const UEngineGraphicDevice& _Other) = delete;
	UEngineGraphicDevice(UEngineGraphicDevice&& _Other) noexcept = delete;
	UEngineGraphicDevice& operator=(const UEngineGraphicDevice& _Other) = delete;
	UEngineGraphicDevice& operator=(UEngineGraphicDevice&& _Other) noexcept = delete;

	void Initialize(const UEngineWindow& _Window);

protected:

private:
	struct ID3D11Device* Device = nullptr;
	struct ID3D11DeviceContext* Context = nullptr;
	const class UEngineWindow* WindowPtr;

	struct IDXGIAdapter* GetHighPerFormanceAdapter();
};
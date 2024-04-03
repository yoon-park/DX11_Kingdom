#pragma once

class UEngineCore;
class ULevel;
class UEngineRenderTarget;

class UEngineGraphicDevice
{
	friend UEngineCore;
	friend ULevel;

public:
	UEngineGraphicDevice();
	~UEngineGraphicDevice();

	UEngineGraphicDevice(const UEngineGraphicDevice& _Other) = delete;
	UEngineGraphicDevice(UEngineGraphicDevice&& _Other) noexcept = delete;
	UEngineGraphicDevice& operator=(const UEngineGraphicDevice& _Other) = delete;
	UEngineGraphicDevice& operator=(UEngineGraphicDevice&& _Other) noexcept = delete;

	struct ID3D11Device* GetDevice()
	{
		return Device;
	}

	struct ID3D11DeviceContext* GetContext()
	{
		return Context;
	}

	void Initialize(const UEngineWindow& _Window, const float4& _ClearColor);

	void RenderStart();
	void RenderEnd();

protected:

private:
	struct ID3D11Device* Device = nullptr;
	struct ID3D11DeviceContext* Context = nullptr;
	struct IDXGIAdapter* Adapter = nullptr;
	struct IDXGISwapChain* SwapChain = nullptr;
	const class UEngineWindow* WindowPtr;
	std::shared_ptr<UEngineRenderTarget> BackBufferRenderTarget = nullptr;

	std::shared_ptr<UEngineRenderTarget> GetBackBufferRenderTarget()
	{
		return BackBufferRenderTarget;
	}

	struct IDXGIAdapter* GetHighPerformanceAdapter();
	void CreateSwapChain(const float4& _ClearColor);

	void EngineResourcesInit();
	void EngineResourcesRelease();
};
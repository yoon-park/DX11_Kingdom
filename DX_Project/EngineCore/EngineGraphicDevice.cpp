#include "PreCompile.h"
#include "EngineGraphicDevice.h"

UEngineGraphicDevice::UEngineGraphicDevice()
{

}

UEngineGraphicDevice::~UEngineGraphicDevice()
{
	if (Context != nullptr)
	{
		Context->Release();
	}

	if (Device != nullptr)
	{
		Device->Release();
	}
}

IDXGIAdapter* UEngineGraphicDevice::GetHighPerFormanceAdapter()
{
	IDXGIFactory* Factory = nullptr;
	IDXGIAdapter* Adapter = nullptr;

	HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&Factory));

	if (Factory == nullptr)
	{
		MsgBoxAssert("그래픽카드에서 팩토리 인터페이스를 생성하지 못했습니다.");
		return nullptr;
	}

	size_t VideoMemory = 0;

	for (int Index = 0;; Index++)
	{
		IDXGIAdapter* CurAdapter = nullptr;
		Factory->EnumAdapters(Index, &CurAdapter);

		if (CurAdapter == nullptr)
		{
			break;
		}

		DXGI_ADAPTER_DESC Desc;
		CurAdapter->GetDesc(&Desc);

		if (Desc.DedicatedVideoMemory >= VideoMemory)
		{
			VideoMemory = Desc.DedicatedVideoMemory;

			if (Adapter != nullptr)
			{
				Adapter->Release();
			}

			Adapter = CurAdapter;
			continue;
		}

		CurAdapter->Release();
	}

	Factory->Release();
	return Adapter;
}

void UEngineGraphicDevice::Initialize(const UEngineWindow& _Window)
{
	if (_Window.GetHWND() == nullptr)
	{
		MsgBoxAssert("Open되지 않은 윈도우로 그래픽카드를 초기화하려 시도했습니다.");
		return;
	}

	int iFlag = 0;
#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif
	
	D3D_FEATURE_LEVEL Level = D3D_FEATURE_LEVEL_11_0;
	IDXGIAdapter* Adapter = GetHighPerFormanceAdapter();

	if (Adapter == nullptr)
	{
		MsgBoxAssert("그래픽카드가 존재하지 않습니다.");
		return;
	}

	HRESULT Result = D3D11CreateDevice(
		Adapter,
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN,
		nullptr,
		iFlag,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&Device,
		&Level,
		&Context
	);

	if (Device == nullptr)
	{
		MsgBoxAssert("그래픽카드의 메모리 제어 권한 디바이스를 생성하는데 실패했습니다.");
		return;
	}

	if (Context == nullptr)
	{
		MsgBoxAssert("그래픽카드의 랜더링 제어 권한 컨텍스트를 생성하는데 실패했습니다.");
		return;
	}

	if (Adapter != nullptr)
	{
		Adapter->Release();
	}

	if (Result != S_OK)
	{
		MsgBoxAssert("디바이스 생성에 실패했습니다.");
		return;
	}

	if (Level != D3D_FEATURE_LEVEL_11_0)
	{
		MsgBoxAssert("DirectX 11 버전을 사용할수 없는 그래픽카드입니다.");
		return;
	}

	Result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	if (Result != S_OK)
	{
		MsgBoxAssert("멀티쓰레드 옵션을 사용할 수 없습니다.");
		return;
	}

	WindowPtr = &_Window;
}
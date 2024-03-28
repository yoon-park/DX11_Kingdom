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
		MsgBoxAssert("�׷���ī�忡�� ���丮 �������̽��� �������� ���߽��ϴ�.");
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
		MsgBoxAssert("Open���� ���� ������� �׷���ī�带 �ʱ�ȭ�Ϸ� �õ��߽��ϴ�.");
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
		MsgBoxAssert("�׷���ī�尡 �������� �ʽ��ϴ�.");
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
		MsgBoxAssert("�׷���ī���� �޸� ���� ���� ����̽��� �����ϴµ� �����߽��ϴ�.");
		return;
	}

	if (Context == nullptr)
	{
		MsgBoxAssert("�׷���ī���� ������ ���� ���� ���ؽ�Ʈ�� �����ϴµ� �����߽��ϴ�.");
		return;
	}

	if (Adapter != nullptr)
	{
		Adapter->Release();
	}

	if (Result != S_OK)
	{
		MsgBoxAssert("����̽� ������ �����߽��ϴ�.");
		return;
	}

	if (Level != D3D_FEATURE_LEVEL_11_0)
	{
		MsgBoxAssert("DirectX 11 ������ ����Ҽ� ���� �׷���ī���Դϴ�.");
		return;
	}

	Result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	if (Result != S_OK)
	{
		MsgBoxAssert("��Ƽ������ �ɼ��� ����� �� �����ϴ�.");
		return;
	}

	WindowPtr = &_Window;
}
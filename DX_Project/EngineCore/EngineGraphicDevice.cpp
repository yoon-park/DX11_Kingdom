#include "PreCompile.h"
#include "EngineGraphicDevice.h"

#include "EngineTexture.h"
#include "EngineRenderTarget.h"

UEngineGraphicDevice::UEngineGraphicDevice()
{

}

UEngineGraphicDevice::~UEngineGraphicDevice()
{
	if (SwapChain != nullptr)
	{
		SwapChain->Release();
	}

	if (Context != nullptr)
	{
		Context->Release();
	}

	if (Device != nullptr)
	{
		Device->Release();
	}
}

void UEngineGraphicDevice::Initialize(const UEngineWindow& _Window, const float4& _ClearColor)
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
	Adapter = GetHighPerformanceAdapter();

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
		if (Result != RPC_E_CHANGED_MODE)
		{
			MsgBoxAssert("��Ƽ������ �ɼ��� ����� �� �����ϴ�.");
			return;
		}
	}

	WindowPtr = &_Window;

	CreateSwapChain(_ClearColor);
}

void UEngineGraphicDevice::RenderStart()
{
	BackBufferRenderTarget->Clear();
}

void UEngineGraphicDevice::RenderEnd()
{
	HRESULT Result = SwapChain->Present(0, 0);

	if (Result == DXGI_ERROR_DEVICE_REMOVED || Result == DXGI_ERROR_DEVICE_RESET)
	{
		MsgBoxAssert("�ػ� �Ǵ� ����̽� ���� ������ ���� �Ǿ����ϴ�.");
		return;
	}
}

IDXGIAdapter* UEngineGraphicDevice::GetHighPerformanceAdapter()
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

void UEngineGraphicDevice::CreateSwapChain(const float4& _ClearColor)
{
	float4 Resolution = WindowPtr->GetWindowScale();

	DXGI_SWAP_CHAIN_DESC ScInfo = { 0 };
	ScInfo.BufferCount = 2;
	ScInfo.BufferDesc.Width = Resolution.iX();
	ScInfo.BufferDesc.Height = Resolution.iY();
	ScInfo.OutputWindow = WindowPtr->GetHWND();
	ScInfo.BufferDesc.RefreshRate.Denominator = 1;
	ScInfo.BufferDesc.RefreshRate.Numerator = 60;
	ScInfo.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	ScInfo.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	ScInfo.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	ScInfo.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
	ScInfo.SampleDesc.Quality = 0;
	ScInfo.SampleDesc.Count = 1;
	ScInfo.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
	ScInfo.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	ScInfo.Windowed = true;

	IDXGIFactory* pF = nullptr;

	Adapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pF));
	pF->CreateSwapChain(Device, &ScInfo, &SwapChain);

	Adapter->Release();
	pF->Release();

	ID3D11Texture2D* DXBackBufferTexture = nullptr;
	
	if (SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&DXBackBufferTexture)) != S_OK)
	{
		MsgBoxAssert("����� �ؽ�ó�� ������ ���߽��ϴ�.");
		return;
	}

	std::shared_ptr<UEngineTexture> Texture = UEngineTexture::Create(DXBackBufferTexture);
	BackBufferRenderTarget = UEngineRenderTarget::Create(Texture, _ClearColor);
}
#include "PreCompile.h"
#include "EngineBlend.h"

#include "EngineCore.h"

UEngineBlend::UEngineBlend()
{

}

UEngineBlend::~UEngineBlend()
{
	if (State != nullptr)
	{
		State->Release();
	}
}

void UEngineBlend::ResCreate(const D3D11_BLEND_DESC& _Info)
{
	HRESULT Result = GEngine->GetDirectXDevice()->CreateBlendState(&_Info, &State);

#ifdef _DEBUG
	if (Result != S_OK)
	{
		MsgBoxAssert("���� ������ �����߽��ϴ�.");
		return;
	}
#endif
}

void UEngineBlend::Setting()
{
#ifdef _DEBUG
	if (State == nullptr)
	{
		MsgBoxAssert("��������� ���� ���带 �����Ϸ� �߽��ϴ�. : " + GetName());
	}
#endif

	GEngine->GetDirectXContext()->OMSetBlendState(State, Factor.Arr1D, Mask);
}
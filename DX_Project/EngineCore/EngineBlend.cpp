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
		MsgBoxAssert("블렌드 생성에 실패했습니다.");
		return;
	}
#endif
}

void UEngineBlend::Setting()
{
#ifdef _DEBUG
	if (State == nullptr)
	{
		MsgBoxAssert("만들어지지 않은 블렌드를 세팅하려 했습니다. : " + GetName());
	}
#endif

	GEngine->GetDirectXContext()->OMSetBlendState(State, Factor.Arr1D, Mask);
}
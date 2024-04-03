#include "PreCompile.h"
#include "EngineRasterizer.h"

#include "EngineCore.h"

UEngineRasterizer::UEngineRasterizer()
{

}

UEngineRasterizer::~UEngineRasterizer()
{
	if (State != nullptr)
	{
		State->Release();
	}
}

void UEngineRasterizer::ResCreate(const D3D11_RASTERIZER_DESC& _Info)
{
	HRESULT Result = GEngine->GetDirectXDevice()->CreateRasterizerState(&_Info, &State);
	
#ifdef _DEBUG
	if (Result != S_OK)
	{
		MsgBoxAssert("래스터라이저 생성에 실패했습니다.");
		return;
	}
#endif
}

void UEngineRasterizer::Setting()
{
#ifdef _DEBUG
	if (State == nullptr)
	{
		MsgBoxAssert("만들어지지 않은 래스터라이저를 세팅하려 했습니다. : " + GetName());
	}
#endif

	GEngine->GetDirectXContext()->RSSetState(State);
}
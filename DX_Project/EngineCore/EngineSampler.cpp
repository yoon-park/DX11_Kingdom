#include "PreCompile.h"
#include "EngineSampler.h"

#include "EngineCore.h"

UEngineSampler::UEngineSampler()
{

}

UEngineSampler::~UEngineSampler()
{
	if (State != nullptr)
	{
		State->Release();
	}
}

void UEngineSampler::ResCreate(const D3D11_SAMPLER_DESC& _Info)
{
	HRESULT Result = GEngine->GetDirectXDevice()->CreateSamplerState(&_Info, &State);
#ifdef _DEBUG
	if (Result != S_OK)
	{
		MsgBoxAssert("���÷� ������ �����߽��ϴ�.");
		return;
	}
#endif
}

void UEngineSampler::Setting(EShaderType _Type, UINT _Slot)
{
	switch (_Type)
	{
	case EShaderType::Vertex:
		GEngine->GetDirectXContext()->VSSetSamplers(_Slot, 1, &State);
		break;
	case EShaderType::Pixel:
		GEngine->GetDirectXContext()->PSSetSamplers(_Slot, 1, &State);
		break;
	case EShaderType::NONE:
	default:
		MsgBoxAssert("Ÿ���� �Һи��� ���÷� �����Դϴ�.");
		break;
	}
}
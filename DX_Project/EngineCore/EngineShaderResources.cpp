#include "PreCompile.h"
#include "EngineShaderResources.h"

void UEngineConstantBufferSetter::Setting()
{
	Res->ChangeData(CPUData, BufferSize);
	Res->Setting(Type, Slot);
}

bool UEngineShaderResources::IsConstantBuffer(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	for (std::pair<const EShaderType, std::map<std::string, UEngineConstantBufferSetter>>& Pair : ConstantBuffers)
	{
		std::map<std::string, UEngineConstantBufferSetter>& ResMap = Pair.second;

		if (ResMap.contains(UpperName) == true)
		{
			return true;
		}
	}

	return false;
}

void UEngineShaderResources::SettingConstantBuffer(std::string_view _Name, const void* _Data, UINT _Size)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	for (std::pair<const EShaderType, std::map<std::string, UEngineConstantBufferSetter>>& Pair : ConstantBuffers)
	{
		std::map<std::string, UEngineConstantBufferSetter>& ResMap = Pair.second;

		if (ResMap.contains(UpperName) == false)
		{
			continue;
		}

		UEngineConstantBufferSetter& Setter = ResMap[UpperName];

		if (_Size != Setter.BufferSize)
		{
			MsgBoxAssert(Setter.Res->GetName() + "의 바이트 크기가 다릅니다. : " + std::to_string(Setter.BufferSize) + " Vs " + std::to_string(_Size));
		}

		Setter.CPUData = _Data;
	}
}

void UEngineShaderResources::SettingAllShaderResources()
{
	for (std::pair<const EShaderType, std::map<std::string, UEngineConstantBufferSetter>>& Pair : ConstantBuffers)
	{
		std::map<std::string, UEngineConstantBufferSetter>& ResMap = Pair.second;

		for (std::pair<const std::string, UEngineConstantBufferSetter>& Setter : ResMap)
		{
			Setter.second.Setting();
		}
	}
}

void UEngineShaderResources::ShaderResourcesCheck(
	EShaderType _Type,
	std::string_view _EntryName,
	ID3DBlob* _ShaderCode
)
{
	if (_ShaderCode == nullptr)
	{
		MsgBoxAssert("컴파일 실패한 쉐이더에서 리소스를 체크하려 했습니다.");
		return;
	}

	ID3DBlob* ShaderCode = _ShaderCode;
	ID3D11ShaderReflection* CompileInfo = nullptr;

	if (D3DReflect(ShaderCode->GetBufferPointer(), ShaderCode->GetBufferSize(), IID_ID3D11ShaderReflection, reinterpret_cast<void**>(&CompileInfo)) != S_OK)
	{
		MsgBoxAssert("쉐이더 정보수집에 실패했습니다.");
		return;
	}

	D3D11_SHADER_DESC Info = {};
	CompileInfo->GetDesc(&Info);

	for (UINT i = 0; i < Info.BoundResources; i++)
	{
		D3D11_SHADER_INPUT_BIND_DESC ResDesc;

		CompileInfo->GetResourceBindingDesc(i, &ResDesc);

		D3D_SHADER_INPUT_TYPE Type = ResDesc.Type;

		switch (Type)
		{
		case D3D_SIT_CBUFFER:
		{
			ID3D11ShaderReflectionConstantBuffer* BufferInfo = CompileInfo->GetConstantBufferByName(ResDesc.Name);
			D3D11_SHADER_BUFFER_DESC ConstantBufferDesc = {};

			BufferInfo->GetDesc(&ConstantBufferDesc);

			_EntryName;
			std::shared_ptr<UEngineConstantBuffer> Buffer = UEngineConstantBuffer::CreateAndFind(_Type, ResDesc.Name, ConstantBufferDesc.Size);
			std::string UpperName = UEngineString::ToUpper(ResDesc.Name);
			
			UEngineConstantBufferSetter& NewSetter = ConstantBuffers[_Type][UpperName];
			NewSetter.Type = _Type;
			NewSetter.Slot = ResDesc.BindPoint;
			NewSetter.BufferSize = ConstantBufferDesc.Size;
			NewSetter.Res = Buffer;

			break;
		}
		case D3D_SIT_TEXTURE:
			break;
		case D3D_SIT_SAMPLER:
			break;
		default:
			MsgBoxAssert("처리할 수 없는 타입입니다.");
			break;
		}
	}

	CompileInfo->Release();
}
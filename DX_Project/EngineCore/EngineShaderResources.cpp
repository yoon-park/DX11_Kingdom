#include "PreCompile.h"
#include "EngineShaderResources.h"

void UEngineShaderResources::ShaderResourcesCheck(
	EShaderType _Type,
	std::string_view _EntryName,
	ID3DBlob* _ShaderCode
)
{
	if (_ShaderCode == nullptr)
	{
		MsgBoxAssert("������ ������ ���̴����� ���ҽ��� üũ�Ϸ� �߽��ϴ�.");
		return;
	}

	ID3DBlob* ShaderCode = _ShaderCode;
	ID3D11ShaderReflection* CompileInfo = nullptr;

	if (D3DReflect(ShaderCode->GetBufferPointer(), ShaderCode->GetBufferSize(), IID_ID3D11ShaderReflection, reinterpret_cast<void**>(&CompileInfo)) != S_OK)
	{
		MsgBoxAssert("���̴� ���������� �����߽��ϴ�.");
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
			ConstantBuffers[_Type][UpperName].Res = Buffer;

			break;
		}
		case D3D_SIT_TEXTURE:
			break;
		case D3D_SIT_SAMPLER:
			break;
		default:
			MsgBoxAssert("ó���� �� ���� Ÿ���Դϴ�.");
			break;
		}
	}

	CompileInfo->Release();
}
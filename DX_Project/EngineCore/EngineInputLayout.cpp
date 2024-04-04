#include "PreCompile.h"
#include "EngineInputLayout.h"

#include "EngineCore.h"
#include "EngineVertex.h"
#include "EngineVertexBuffer.h"
#include "EngineVertexShader.h"

UEngineInputLayout::UEngineInputLayout()
{

}

UEngineInputLayout::~UEngineInputLayout()
{
	if (Layout != nullptr)
	{
		Layout->Release();
	}
}

void UEngineInputLayout::ResCreate(
	std::shared_ptr<UEngineVertexBuffer> _Buffer,
	std::shared_ptr<UEngineVertexShader> _Shader
)
{
	if (_Buffer == nullptr)
	{
		MsgBoxAssert("��ǲ ���̾ƿ��� ������ �� ���۰� nullptr�Դϴ�.");
	}

	UVertexLayoutInfo* Ptr = _Buffer->LayoutInfoPtr;
	std::vector<D3D11_INPUT_ELEMENT_DESC>& Desc = Ptr->Descs;

	if (_Shader == nullptr)
	{
		MsgBoxAssert("��ǲ ���̾ƿ��� ������ �� ���̴��� nullptr�Դϴ�.");
	}

	ID3DBlob* VertexShaderCodeBlob = _Shader->ShaderCodeBlob;

	HRESULT Result = GEngine->GetDirectXDevice()->CreateInputLayout(
		&Desc[0],
		static_cast<UINT>(Desc.size()),
		VertexShaderCodeBlob->GetBufferPointer(),
		VertexShaderCodeBlob->GetBufferSize(),
		&Layout
	);

	if (Result != S_OK)
	{
		MsgBoxAssert("��ǲ ���̾ƿ� ������ �����߽��ϴ�.");
		return;
	}
}

void UEngineInputLayout::Setting()
{
#ifdef _DEBUG
	if (Layout == nullptr)
	{
		MsgBoxAssert("��������� ���� ��ǲ ���̾ƿ��� �����Ϸ� �߽��ϴ�.");
	}
#endif

	GEngine->GetDirectXContext()->IASetInputLayout(Layout);
}
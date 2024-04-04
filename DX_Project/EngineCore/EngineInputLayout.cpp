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
		MsgBoxAssert("인풋 레이아웃을 생성할 때 버퍼가 nullptr입니다.");
	}

	UVertexLayoutInfo* Ptr = _Buffer->LayoutInfoPtr;
	std::vector<D3D11_INPUT_ELEMENT_DESC>& Desc = Ptr->Descs;

	if (_Shader == nullptr)
	{
		MsgBoxAssert("인풋 레이아웃을 생성할 때 쉐이더가 nullptr입니다.");
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
		MsgBoxAssert("인풋 레이아웃 생성에 실패했습니다.");
		return;
	}
}

void UEngineInputLayout::Setting()
{
#ifdef _DEBUG
	if (Layout == nullptr)
	{
		MsgBoxAssert("만들어지지 않은 인풋 레이아웃을 세팅하려 했습니다.");
	}
#endif

	GEngine->GetDirectXContext()->IASetInputLayout(Layout);
}
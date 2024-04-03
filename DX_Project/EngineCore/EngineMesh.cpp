#include "PreCompile.h"
#include "EngineMesh.h"

#include "EngineCore.h"

UEngineMesh::UEngineMesh()
{

}

UEngineMesh::~UEngineMesh()
{

}

void UEngineMesh::ResCreate(std::string_view _VertexName, std::string_view _IndexName)
{
	VertexBuffer = UEngineVertexBuffer::FindRes(_VertexName);
	IndexBuffer = UEngineIndexBuffer::FindRes(_IndexName);

	if (VertexBuffer == nullptr || IndexBuffer == nullptr)
	{
		MsgBoxAssert("�޽� ������ �����߽��ϴ�.");
		return;
	}
}

void UEngineMesh::InputAssembler1Setting()
{
#ifdef _DEBUG
	if (VertexBuffer == nullptr)
	{
		MsgBoxAssert("���ؽ� ���۰� ���õ��� ���� �޽��Դϴ�. : " + GetName());
		return;
	}
#endif

	VertexBuffer->Setting();
}

void UEngineMesh::InputAssembler2Setting()
{
#ifdef _DEBUG
	if (IndexBuffer == nullptr)
	{
		MsgBoxAssert("�ε��� ���۰� ���õ��� ���� �޽��Դϴ�. : " + GetName());
		return;
	}
#endif

	IndexBuffer->Setting();

	GEngine->GetDirectXContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void UEngineMesh::IndexedDraw()
{
	GEngine->GetDirectXContext()->DrawIndexed(IndexBuffer->Count, 0, 0);
}
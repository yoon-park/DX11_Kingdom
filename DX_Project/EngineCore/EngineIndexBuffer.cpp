#include "PreCompile.h"
#include "EngineIndexBuffer.h"

#include "EngineCore.h"

UEngineIndexBuffer::UEngineIndexBuffer()
{

}

UEngineIndexBuffer::~UEngineIndexBuffer()
{

}

void UEngineIndexBuffer::ResCreate(const void* _Data, UINT _Size, UINT _Count)
{
	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = _Data;

	Size = _Size;
	Count = _Count;

	if (Size == 4)
	{
		Format = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
	}
	else if (Size == 2)
	{
		Format = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
	}

	BufferInfo.ByteWidth = static_cast<UINT>(Size * Count);
	BufferInfo.BindFlags = D3D11_BIND_INDEX_BUFFER;
	BufferInfo.CPUAccessFlags = 0;
	BufferInfo.Usage = D3D11_USAGE_DEFAULT;

	if (GEngine->GetDirectXDevice()->CreateBuffer(&BufferInfo, &Data, &Buffer) != S_OK)
	{
		MsgBoxAssert("�ε��� ���� ������ �����߽��ϴ�.");
		return;
	}
}

void UEngineIndexBuffer::Setting()
{
#ifdef _DEBUG
	if (Buffer == nullptr)
	{
		MsgBoxAssert("��������� ���� �ε��� ���۸� �����Ϸ� �߽��ϴ�. : " + GetName());
		return;
	}
#endif

	GEngine->GetDirectXContext()->IASetIndexBuffer(Buffer, Format, Offset);
}
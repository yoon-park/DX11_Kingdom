#include "PreCompile.h"
#include "EngineVertexBuffer.h"

#include "EngineCore.h"

UEngineVertexBuffer::UEngineVertexBuffer()
{

}

UEngineVertexBuffer::~UEngineVertexBuffer()
{

}

void UEngineVertexBuffer::ResCreate(const void* _Data, UINT _Size, UINT _Count)
{
	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = _Data;

	Size = _Size;
	Count = _Count;

	BufferInfo.ByteWidth = static_cast<UINT>(Size * Count);
	BufferInfo.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferInfo.CPUAccessFlags = 0;
	BufferInfo.Usage = D3D11_USAGE_DEFAULT;

	if (GEngine->GetDirectXDevice()->CreateBuffer(&BufferInfo, &Data, &Buffer) != S_OK)
	{
		MsgBoxAssert("버텍스 버퍼 생성에 실패했습니다.");
		return;
	}
}
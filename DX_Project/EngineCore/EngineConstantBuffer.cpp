#include "PreCompile.h"
#include "EngineConstantBuffer.h"

#include "EngineCore.h"

std::map<EShaderType, std::map<std::string, std::map<int, std::shared_ptr<UEngineConstantBuffer>>>> UEngineConstantBuffer::ConstantBuffers;

UEngineConstantBuffer::UEngineConstantBuffer()
{

}

UEngineConstantBuffer::~UEngineConstantBuffer()
{

}

void UEngineConstantBuffer::ChangeData(const void* _Data, UINT _Size)
{
#ifdef _DEBUG
	if (_Data == nullptr)
	{
		MsgBoxAssert(GetName() + " : ������ۿ� nullptr�� �����͸� �����Ϸ� �߽��ϴ�.");
	}

	if (_Size <= 0)
	{
		MsgBoxAssert(GetName() + " : ������ۿ� 0������ �����͸� �����Ϸ� �߽��ϴ�.");
	}
#endif

	D3D11_MAPPED_SUBRESOURCE Data = {};

	GEngine->GetDirectXContext()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &Data);

#ifdef _DEBUG
	if (Data.pData == nullptr)
	{
		MsgBoxAssert(GetName() + " : �׷���ī�尡 ������ �ź��߽��ϴ�.");
	}
#endif

	memcpy_s(Data.pData, BufferInfo.ByteWidth, _Data, BufferInfo.ByteWidth);

	GEngine->GetDirectXContext()->Unmap(Buffer, 0);
}

void UEngineConstantBuffer::ResCreate(UINT _ByteSize)
{
	BufferInfo.ByteWidth = _ByteSize;
	BufferInfo.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BufferInfo.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	BufferInfo.Usage = D3D11_USAGE_DYNAMIC;

	if (GEngine->GetDirectXDevice()->CreateBuffer(&BufferInfo, nullptr, &Buffer) != S_OK)
	{
		MsgBoxAssert("��� ���� ������ �����߽��ϴ�.");
		return;
	}
}

void UEngineConstantBuffer::Setting(EShaderType _Type, UINT _Slot)
{
	switch (_Type)
	{
	case EShaderType::Vertex:
		GEngine->GetDirectXContext()->VSSetConstantBuffers(_Slot, 1, &Buffer);
		break;
	case EShaderType::Pixel:
		GEngine->GetDirectXContext()->PSSetConstantBuffers(_Slot, 1, &Buffer);
		break;
	case EShaderType::NONE:
	default:
		MsgBoxAssert("ó���� �Ϸ���� ���� ��� ���� ���̴� ���� Ÿ���Դϴ�.");
		break;
	}
}
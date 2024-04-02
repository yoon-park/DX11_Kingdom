#pragma once
#include "EngineBuffer.h"

class UEngineVertexBuffer : public UEngineResources<UEngineVertexBuffer>, public UEngineBuffer
{
public:
	UEngineVertexBuffer();
	~UEngineVertexBuffer();

	UEngineVertexBuffer(const UEngineVertexBuffer& _Other) = delete;
	UEngineVertexBuffer(UEngineVertexBuffer&& _Other) noexcept = delete;
	UEngineVertexBuffer& operator=(const UEngineVertexBuffer& _Other) = delete;
	UEngineVertexBuffer& operator=(UEngineVertexBuffer&& _Other) noexcept = delete;

	template<typename VertexType>
	static std::shared_ptr<UEngineVertexBuffer> Create(std::string_view _Name, const std::vector<VertexType> _Data)
	{
		std::shared_ptr<UEngineVertexBuffer> Res = CreateResName(_Name);
		Res->ResCreate(&_Data[0], static_cast<UINT>(sizeof(VertexType)), static_cast<UINT>(_Data.size()));
		return Res;
	}

protected:

private:
	UINT Size = 0;
	UINT Count = 0;

	void ResCreate(const void* _Data, UINT _Size, UINT _Count);
};
#include "PreCompile.h"
#include "EngineSerializer.h"

UEngineSerializer::UEngineSerializer() 
{

}

UEngineSerializer::~UEngineSerializer() 
{

}

void UEngineSerializer::Read(void* _Data, size_t _Size)
{
	memcpy_s(_Data, _Size, &Data[ReadOffset], _Size);
	ReadOffset += static_cast<int>(_Size);
}

void UEngineSerializer::Write(const void* _Data, size_t _Size)
{
	if (Data.size() <= WriteOffset + _Size)
	{
		Data.resize(Data.capacity() * 2 + _Size);
	}

	memcpy_s(&Data[WriteOffset], _Size, _Data, _Size);
	WriteOffset += static_cast<int>(_Size);
}

void UEngineSerializer::WriteText(const std::string& _Text)
{
	Write(_Text.c_str(), _Text.size());
}

void UEngineSerializer::BufferResize(int _Size)
{
	Data.resize(_Size);
}

std::string UEngineSerializer::ToString()
{
	return static_cast<char*>(&Data[0]);
}
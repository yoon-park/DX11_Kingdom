#include "PreCompile.h"
#include "EngineBuffer.h"

UEngineBuffer::UEngineBuffer()
{

}

UEngineBuffer::~UEngineBuffer()
{
	if (Buffer != nullptr)
	{
		Buffer->Release();
	}
}
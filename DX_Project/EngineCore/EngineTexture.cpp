#include "PreCompile.h"
#include "EngineTexture.h"

UEngineTexture::UEngineTexture()
{

}

UEngineTexture::~UEngineTexture()
{
	if (Texture != nullptr)
	{
		Texture->Release();
	}
}
#include "PreCompile.h"
#include "EngineShader.h"

UEngineShader::UEngineShader()
{

}

UEngineShader::~UEngineShader()
{
	if (ErrorCodeBlob != nullptr)
	{
		ErrorCodeBlob->Release();
	}

	if (ShaderCodeBlob != nullptr)
	{
		ShaderCodeBlob->Release();
	}
}

void UEngineShader::ShaderResCheck()
{
	Resources.ShaderResourcesCheck(EntryName, ShaderCodeBlob);
}
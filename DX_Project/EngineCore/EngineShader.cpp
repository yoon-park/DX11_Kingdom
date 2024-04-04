#include "PreCompile.h"
#include "EngineShader.h"

#include "EngineShaderResources.h"

UEngineShader::UEngineShader()
{
	Resources = std::make_shared<UEngineShaderResources>();
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
	Resources->ShaderResourcesCheck(Type, EntryName, ShaderCodeBlob);
}
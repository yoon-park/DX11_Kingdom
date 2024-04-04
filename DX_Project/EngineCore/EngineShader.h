#pragma once
#include "EngineEnums.h"

class UEngineInputLayout;
class UEngineShaderResources;

class UEngineShader
{
	friend UEngineInputLayout;

public:
	UEngineShader();
	~UEngineShader();

	UEngineShader(const UEngineShader& _Other) = delete;
	UEngineShader(UEngineShader&& _Other) noexcept = delete;
	UEngineShader& operator=(const UEngineShader& _Other) = delete;
	UEngineShader& operator=(UEngineShader&& _Other) noexcept = delete;

	std::shared_ptr<UEngineShaderResources> Resources;

protected:
	ID3DBlob* ShaderCodeBlob = nullptr;
	ID3DBlob* ErrorCodeBlob = nullptr;
	EShaderType Type = EShaderType::NONE;
	std::string EntryName = "NONE";

	void ShaderResCheck();

private:

};
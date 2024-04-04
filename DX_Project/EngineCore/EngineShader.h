#pragma once
#include "EngineShaderResources.h"

class UEngineInputLayout;

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

	UEngineShaderResources Resources;

protected:
	ID3DBlob* ShaderCodeBlob = nullptr;
	ID3DBlob* ErrorCodeBlob = nullptr;
	std::string EntryName = "NONE";

	void ShaderResCheck();

private:

};
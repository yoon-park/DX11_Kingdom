#pragma once
#include "EngineEnums.h"
#include "EngineConstantBuffer.h"

class UEngineConstantBufferSetter
{
public:
	std::shared_ptr<class UEngineConstantBuffer> Res;
	void* SettingCPU = nullptr;
};

class URenderer;
class UEngineShader;

class UEngineShaderResources
{
	friend URenderer;
	friend UEngineShader;

public:

protected:

private:
	std::map<EShaderType, std::map<std::string, UEngineConstantBufferSetter>> ConstantBuffers;

	void ShaderResourcesCheck(EShaderType _Type, std::string_view _EntryName, ID3DBlob* _ShaderCode);
};
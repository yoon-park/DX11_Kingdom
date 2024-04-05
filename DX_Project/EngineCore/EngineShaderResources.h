#pragma once
#include "EngineEnums.h"
#include "EngineConstantBuffer.h"

class USetterBase
{
public:
	EShaderType Type = EShaderType::NONE;
	int Slot = -1;
};

class UEngineConstantBufferSetter : public USetterBase
{
public:
	const void* CPUData = nullptr;
	UINT BufferSize = 0;
	std::shared_ptr<class UEngineConstantBuffer> Res;

	void Setting();
};

class URenderer;
class UEngineShader;

class UEngineShaderResources
{
	friend URenderer;
	friend UEngineShader;

public:
	bool IsConstantBuffer(std::string_view _Name);

	template<typename Value>
	void SettingConstantBuffer(std::string_view _Name, Value& _Data)
	{
		SettingConstantBuffer(_Name, &_Data, static_cast<UINT>(sizeof(Value)));
	}

	void SettingConstantBuffer(std::string_view _Name, const void* _Data, UINT _Size);

	void SettingAllShaderResources();

protected:

private:
	std::map<EShaderType, std::map<std::string, UEngineConstantBufferSetter>> ConstantBuffers;

	void ShaderResourcesCheck(EShaderType _Type, std::string_view _EntryName, ID3DBlob* _ShaderCode);
};
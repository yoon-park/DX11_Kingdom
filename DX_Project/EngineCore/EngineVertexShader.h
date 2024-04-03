#pragma once
#include "EngineShader.h"

class UEngineMaterial;

class UEngineVertexShader : public UEngineResources<UEngineVertexShader>, public UEngineShader
{
	friend UEngineMaterial;

public:
	UEngineVertexShader();
	~UEngineVertexShader();

	UEngineVertexShader(const UEngineVertexShader& _Other) = delete;
	UEngineVertexShader(UEngineVertexShader&& _Other) noexcept = delete;
	UEngineVertexShader& operator=(const UEngineVertexShader& _Other) = delete;
	UEngineVertexShader& operator=(UEngineVertexShader&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineVertexShader> Load(
		std::string_view _Path,
		std::string_view _EntryPoint,
		UINT _High = 5,
		UINT _Low = 0)
	{
		std::shared_ptr<UEngineVertexShader> Res = CreateResName(_Path);
		Res->ResLoad(_EntryPoint, _High, _Low);
		return Res;
	}

	static std::shared_ptr<UEngineVertexShader> Load(
		std::string_view _Name,
		std::string_view _Path,
		std::string_view _EntryPoint,
		UINT _High = 5,
		UINT _Low = 0)
	{
		std::shared_ptr<UEngineVertexShader> Res = CreateResName(_Name, _Path);
		Res->ResLoad(_EntryPoint, _High, _Low);
		return Res;
	}

protected:

private:
	ID3D11VertexShader* ShaderPtr = nullptr;

	void ResLoad(std::string_view _EntryPoint, UINT _High, UINT Low);
	void Setting();
};
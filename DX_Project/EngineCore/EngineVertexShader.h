#pragma once
#include "EngineShader.h"

#include "EngineInputLayout.h"

class UEngineInputLayout;
class UEngineMaterial;

class UEngineVertexShader : public UEngineResources<UEngineVertexShader>, public UEngineShader
{
	friend UEngineInputLayout;
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
		UINT _Low = 0
	)
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
		UINT _Low = 0
	)
	{
		std::shared_ptr<UEngineVertexShader> Res = CreateResName(_Path, _Name);
		Res->ResLoad(_EntryPoint, _High, _Low);
		return Res;
	}

protected:

private:
	ID3D11VertexShader* ShaderPtr = nullptr;
	ID3D11InputLayout* Layout = nullptr;
	std::shared_ptr<UEngineInputLayout> InputLayout;

	void ResLoad(std::string_view _EntryPoint, UINT _High, UINT Low);
	void Setting();
};
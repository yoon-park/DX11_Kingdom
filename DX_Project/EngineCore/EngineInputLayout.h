#pragma once

class URenderer;
class UEngineVertexBuffer;
class UEngineVertexShader;

class UEngineInputLayout : public UEngineResources<UEngineInputLayout>
{
	friend URenderer;

public:
	UEngineInputLayout();
	~UEngineInputLayout();

	UEngineInputLayout(const UEngineInputLayout& _Other) = delete;
	UEngineInputLayout(UEngineInputLayout&& _Other) noexcept = delete;
	UEngineInputLayout& operator=(const UEngineInputLayout& _Other) = delete;
	UEngineInputLayout& operator=(UEngineInputLayout&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineInputLayout> Create(
		std::shared_ptr<UEngineVertexBuffer> _Buffer,
		std::shared_ptr<UEngineVertexShader> _Shader
	)
	{
		std::shared_ptr<UEngineInputLayout> Res = CreateResUnName();
		Res->ResCreate(_Buffer, _Shader);
		return Res;
	}

protected:

private:
	ID3D11InputLayout* Layout = nullptr;

	void ResCreate(std::shared_ptr<UEngineVertexBuffer> _Buffer, std::shared_ptr<UEngineVertexShader> _Shader);
	void Setting();
};
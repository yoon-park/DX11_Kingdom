#include "PreCompile.h"
#include "EngineMaterial.h"

UEngineMaterial::UEngineMaterial()
{
	SetRasterizer("EngineBase");
	SetBlend("EngineBase");
}

UEngineMaterial::~UEngineMaterial()
{

}

void UEngineMaterial::SetVertexShader(std::string_view _Name)
{
	VertexShader = UEngineVertexShader::FindRes(_Name);

	if (VertexShader == nullptr)
	{
		MsgBoxAssert("존재하지 않는 버텍스 쉐이더를 세팅하려 했습니다.");
		return;
	}
}

void UEngineMaterial::SetPixelShader(std::string_view _Name)
{
	PixelShader = UEnginePixelShader::FindRes(_Name);

	if (PixelShader == nullptr)
	{
		MsgBoxAssert("존재하지 않는 픽셀 쉐이더를 세팅하려 했습니다.");
		return;
	}
}

void UEngineMaterial::SetRasterizer(std::string_view _Name)
{
	Rasterizer = UEngineRasterizer::FindRes(_Name);

	if (Rasterizer == nullptr)
	{
		MsgBoxAssert("존재하지 않는 래스터라이저를 세팅하려 했습니다.");
		return;
	}
}

void UEngineMaterial::SetBlend(std::string_view _Name)
{
	Blend = UEngineBlend::FindRes(_Name);

	if (Blend == nullptr)
	{
		MsgBoxAssert("존재하지 않는 블렌드를 세팅하려 했습니다.");
		return;
	}
}

void UEngineMaterial::VertexShaderSetting()
{
#ifdef _DEBUG
	if (VertexShader == nullptr)
	{
		MsgBoxAssert("버텍스 쉐이더를 세팅하지 않고 렌더하려 했습니다.");
		return;
	}
#endif

	VertexShader->Setting();
}

void UEngineMaterial::PixelShaderSetting()
{
#ifdef _DEBUG
	if (PixelShader == nullptr)
	{
		MsgBoxAssert("픽셀 쉐이더를 세팅하지 않고 랜더하려 했습니다.");
		return;
	}
#endif

	PixelShader->Setting();
}

void UEngineMaterial::RasterizerSetting()
{
#ifdef _DEBUG
	if (Rasterizer == nullptr)
	{
		MsgBoxAssert("래스터라이저를 세팅하지 않고 랜더하려 했습니다.");
		return;
	}
#endif

	Rasterizer->Setting();
}

void UEngineMaterial::BlendSetting()
{
#ifdef _DEBUG
	if (Blend == nullptr)
	{
		MsgBoxAssert("블렌드를 세팅하지 않고 랜더하려 했습니다.");
		return;
	}
#endif

	Blend->Setting();
}
#include "PreCompile.h"
#include "EngineMaterial.h"

UEngineMaterial::UEngineMaterial()
{

}

UEngineMaterial::~UEngineMaterial()
{

}

void UEngineMaterial::SetVertexShader(std::string_view _Name)
{
	VertexShader = UEngineVertexShader::FindRes(_Name);

	if (VertexShader == nullptr)
	{
		MsgBoxAssert("�������� �ʴ� ���ؽ� ���̴��� �����Ϸ� �߽��ϴ�.");
		return;
	}
}

void UEngineMaterial::SetRasterizer(std::string_view _Name)
{
	Rasterizer = UEngineRasterizer::FindRes(_Name);

	if (Rasterizer == nullptr)
	{
		MsgBoxAssert("�������� �ʴ� �����Ͷ������� �����Ϸ� �߽��ϴ�.");
		return;
	}
}

void UEngineMaterial::SetPixelShader(std::string_view _Name)
{
	PixelShader = UEnginePixelShader::FindRes(_Name);

	if (PixelShader == nullptr)
	{
		MsgBoxAssert("�������� �ʴ� �ȼ� ���̴��� �����Ϸ� �߽��ϴ�.");
		return;
	}
}

void UEngineMaterial::VertexShaderSetting()
{
#ifdef _DEBUG
	if (VertexShader == nullptr)
	{
		MsgBoxAssert("���ؽ� ���̴��� �������� �ʰ� �����Ϸ� �߽��ϴ�.");
		return;
	}
#endif

	VertexShader->Setting();
}

void UEngineMaterial::RasterizerSetting()
{
#ifdef _DEBUG
	if (Rasterizer == nullptr)
	{
		MsgBoxAssert("�����Ͷ������� �������� �ʰ� �����Ϸ� �߽��ϴ�.");
		return;
	}
#endif

	Rasterizer->Setting();
}

void UEngineMaterial::PixelShaderSetting()
{
#ifdef _DEBUG
	if (PixelShader == nullptr)
	{
		MsgBoxAssert("�ȼ� ���̴��� �������� �ʰ� �����Ϸ� �߽��ϴ�.");
		return;
	}
#endif

	PixelShader->Setting();
}
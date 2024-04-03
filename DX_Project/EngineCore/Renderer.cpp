#include "PreCompile.h"
#include "Renderer.h"

URenderer::URenderer()
{

}

URenderer::~URenderer()
{

}

void URenderer::SetMesh(std::string_view _Name)
{
	Mesh = UEngineMesh::FindRes(_Name);

	if (Mesh == nullptr)
	{
		MsgBoxAssert("존재하지 않는 메쉬를 세팅하려 했습니다. : " + std::string(_Name));
		return;
	}

}

void URenderer::SetMaterial(std::string_view _Name)
{
	Material = UEngineMaterial::FindRes(_Name);

	if (Material == nullptr)
	{
		MsgBoxAssert("존재하지 않는 머티리얼을 세팅하려고 했습니다. : " + std::string(_Name));
		return;
	}
}

void URenderer::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->PushRenderer(shared_from_this());
}

void URenderer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void URenderer::Render(float _DeltaTime)
{
	Mesh->InputAssembler1Setting();
	Material->VertexShaderSetting();
	Mesh->InputAssembler2Setting();
	Material->RasterizerSetting();
	Material->PixelShaderSetting();

	Mesh->IndexedDraw();
}
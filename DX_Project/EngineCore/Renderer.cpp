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
		MsgBoxAssert("�������� �ʴ� �޽��� �����Ϸ� �߽��ϴ�. : " + std::string(_Name));
		return;
	}

	if (Material != nullptr)
	{
		Layout = UEngineInputLayout::Create(Mesh->VertexBuffer, Material->GetVertexShader());
	}
}

void URenderer::SetMaterial(std::string_view _Name)
{
	Material = UEngineMaterial::FindRes(_Name);

	if (Material == nullptr)
	{
		MsgBoxAssert("�������� �ʴ� ��Ƽ������ �����Ϸ��� �߽��ϴ�. : " + std::string(_Name));
		return;
	}

	if (Mesh != nullptr)
	{
		Layout = UEngineInputLayout::Create(Mesh->VertexBuffer, Material->GetVertexShader());
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
	// Input Assembler1
	Mesh->InputAssembler1Setting();
	Layout->Setting();

	// Vertex Shader
	Material->VertexShaderSetting();

	// Input Assembler2
	Mesh->InputAssembler2Setting();

	// Rasterizer
	Material->RasterizerSetting();

	// Pixel Shader
	Material->PixelShaderSetting();

	// OM

	// Draw
	Mesh->IndexedDraw();
}
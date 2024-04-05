#include "PreCompile.h"
#include "Renderer.h"

URenderer::URenderer()
{
	Resources = std::make_shared<UEngineShaderResources>();
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
		MsgBoxAssert("존재하지 않는 머티리얼을 세팅하려고 했습니다. : " + std::string(_Name));
		return;
	}

	if (Mesh != nullptr)
	{
		Layout = UEngineInputLayout::Create(Mesh->VertexBuffer, Material->GetVertexShader());
	}

	ResCopy();

	if (Resources->IsConstantBuffer("FTransform") == true)
	{
		Resources->SettingConstantBuffer("FTransform", Transform);
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

void URenderer::ResCopy()
{
	if (Material->GetVertexShader() != nullptr)
	{
		std::map<EShaderType, std::map<std::string, UEngineConstantBufferSetter>>& RendererConstantBuffers = Resources->ConstantBuffers;
		std::shared_ptr<UEngineShaderResources> ShaderResources = Material->GetVertexShader()->Resources;

		std::map<EShaderType, std::map<std::string, UEngineConstantBufferSetter>>& ShaderConstantBuffers = ShaderResources->ConstantBuffers;

		for (std::pair<const EShaderType, std::map<std::string, UEngineConstantBufferSetter>> Setters : ShaderConstantBuffers)
		{
			for (std::pair<const std::string, UEngineConstantBufferSetter> ConstantBufferSetter : Setters.second)
			{
				RendererConstantBuffers[Setters.first][ConstantBufferSetter.first] = ConstantBufferSetter.second;
			}
		}
	}
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
	Resources->SettingAllShaderResources();

	// OM

	// Draw
	Mesh->IndexedDraw();
}
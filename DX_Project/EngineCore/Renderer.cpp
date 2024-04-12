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

	Resources->Reset();
	ResCopy(Material->GetVertexShader().get());
	ResCopy(Material->GetPixelShader().get());

	if (Resources->IsConstantBuffer("FTransform") == true)
	{
		Resources->SettingConstantBuffer("FTransform", Transform);
	}

	MaterialSettingEnd();
}

void URenderer::SetOrder(int _Order)
{
	int PrevOrder = GetOrder();

	Super::SetOrder(_Order);

	GetWorld()->ChangeOrderRenderer(shared_from_this(), PrevOrder, _Order);
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

void URenderer::ResCopy(UEngineShader* _Shader)
{
	{
		std::map<EShaderType, std::map<std::string, UEngineConstantBufferSetter>>& RendererConstantBuffers
			= Resources->ConstantBuffers;

		std::shared_ptr<UEngineShaderResources> ShaderResources = _Shader->Resources;
		std::map<EShaderType, std::map<std::string, UEngineConstantBufferSetter>>& ShaderConstantBuffers
			= ShaderResources->ConstantBuffers;

		for (std::pair<const EShaderType, std::map<std::string, UEngineConstantBufferSetter>> Setters : ShaderConstantBuffers)
		{
			for (std::pair<const std::string, UEngineConstantBufferSetter> Setter : Setters.second)
			{
				RendererConstantBuffers[Setters.first][Setter.first] = Setter.second;
			}
		}
	}

	{
		std::map<EShaderType, std::map<std::string, UEngineTextureSetter>>& RendererTexture
			= Resources->Textures;

		std::shared_ptr<UEngineShaderResources> ShaderResources = _Shader->Resources;
		std::map<EShaderType, std::map<std::string, UEngineTextureSetter>>& ShaderTextures
			= ShaderResources->Textures;

		for (std::pair<const EShaderType, std::map<std::string, UEngineTextureSetter>> Setters : ShaderTextures)
		{
			for (std::pair<const std::string, UEngineTextureSetter> Setter : Setters.second)
			{
				RendererTexture[Setters.first][Setter.first] = Setter.second;
			}
		}
	}

	{
		std::map<EShaderType, std::map<std::string, UEngineSamplerSetter>>& RendererSampler
			= Resources->Samplers;

		std::shared_ptr<UEngineShaderResources> ShaderResources = _Shader->Resources;
		std::map<EShaderType, std::map<std::string, UEngineSamplerSetter>>& ShaderSamplers
			= ShaderResources->Samplers;

		for (std::pair<const EShaderType, std::map<std::string, UEngineSamplerSetter>> Setters : ShaderSamplers)
		{
			for (std::pair<const std::string, UEngineSamplerSetter> Setter : Setters.second)
			{
				RendererSampler[Setters.first][Setter.first] = Setter.second;
			}
		}
	}
}

void URenderer::RenderingTransformUpdate(std::shared_ptr<UCamera> _Camera)
{
	Transform.CalculateViewAndProjection(_Camera->GetView(), _Camera->GetProjection());
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
	Material->BlendSetting();
	Resources->SettingAllShaderResources();

	// Draw
	Mesh->IndexedDraw();
}
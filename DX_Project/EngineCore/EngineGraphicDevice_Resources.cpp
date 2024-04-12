#include "PreCompile.h"
#include "EngineGraphicDevice.h"

#include "EngineTexture.h"
#include "EngineVertex.h"
#include "EngineMesh.h"
#include "EngineMaterial.h"
#include "EngineVertexShader.h"
#include "EnginePixelShader.h"
#include "EngineRasterizer.h"
#include "EngineBlend.h"

void MeshInit()
{
	FEngineVertex::Info.AddInputLayout("POSITION", DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT);
	FEngineVertex::Info.AddInputLayout("TEXCOORD", DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT);
	
	{
		std::vector<FEngineVertex> VertexData;
		VertexData.resize(4);

		{
			VertexData[0] = { {-0.5f, 0.5f, 0.0f, 1.0f} , {0.0f, 0.0f} };
			VertexData[1] = { {0.5f, 0.5f, 0.0f, 1.0f} , {1.0f, 0.0f} };
			VertexData[2] = { {0.5f, -0.5f, 0.0f, 1.0f}, {1.0f, 1.0f} };
			VertexData[3] = { {-0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 1.0f} };

			std::shared_ptr<UEngineVertexBuffer> VertexBuffer = UEngineVertexBuffer::Create("Rect", VertexData);
		}

		std::vector<UINT> IndexData = { 0, 1, 2, 0, 2, 3 };
		std::shared_ptr<UEngineIndexBuffer> IndexBuffer = UEngineIndexBuffer::Create("Rect", IndexData);

		UEngineMesh::Create("Rect");

		{
			VertexData[0].POSITION *= 2.0f;
			VertexData[1].POSITION *= 2.0f;
			VertexData[2].POSITION *= 2.0f;
			VertexData[3].POSITION *= 2.0f;

			std::shared_ptr<UEngineVertexBuffer> VertexBuffer = UEngineVertexBuffer::Create("FullRect", VertexData);
		}

		UEngineMesh::Create("FullRect", "FullRect", "Rect");
	}
}

void ShaderInit()
{
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("EngineShader");

	std::vector<UEngineFile> Files = Dir.GetAllFile({ ".fx", "hlsl" });

	for (size_t i = 0; i < Files.size(); i++)
	{
		std::string FullPath = Files[i].GetFullPath();
		std::string AllShaderCode = Files[i].GetString();

		{
			size_t ShaderEntryEnd = AllShaderCode.find("_VS("/*, 0*/);

			if (ShaderEntryEnd != std::string::npos)
			{
				size_t ShaderEntryStart = AllShaderCode.rfind(" ", ShaderEntryEnd);
				std::string EntryName = AllShaderCode.substr(ShaderEntryStart + 1, ShaderEntryEnd - ShaderEntryStart - 1);
				EntryName += "_VS";

				UEngineVertexShader::Load(FullPath.c_str(), EntryName);
			}
		}

		{
			size_t ShaderEntryEnd = AllShaderCode.find("_PS("/*, 0*/);

			if (ShaderEntryEnd != std::string::npos)
			{
				size_t ShaderEntryStart = AllShaderCode.rfind(" ", ShaderEntryEnd);
				std::string EntryName = AllShaderCode.substr(ShaderEntryStart + 1, ShaderEntryEnd - ShaderEntryStart - 1);
				EntryName += "_PS";

				UEnginePixelShader::Load(FullPath.c_str(), EntryName);
			}
		}
	}
}

void SettingInit()
{
	{
		D3D11_RASTERIZER_DESC Desc = {};
		Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		Desc.AntialiasedLineEnable = TRUE;
		Desc.DepthClipEnable = TRUE;

		UEngineRasterizer::Create("EngineBase", Desc);
	}

	{
		D3D11_SAMPLER_DESC Desc = {};
		Desc.AddressW = Desc.AddressV = Desc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.Filter = D3D11_FILTER::D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;
		Desc.MipLODBias = 0.0f;
		Desc.MaxAnisotropy = 1;
		Desc.ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;
		Desc.MinLOD = -FLT_MAX;
		Desc.MaxLOD = FLT_MAX;

		UEngineSampler::Create("POINT", Desc);
	}

	{
		D3D11_SAMPLER_DESC Desc = {};
		Desc.AddressW = Desc.AddressV = Desc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		Desc.MipLODBias = 0.0f;
		Desc.MaxAnisotropy = 1;
		Desc.ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;
		Desc.MinLOD = -FLT_MAX;
		Desc.MaxLOD = FLT_MAX;

		UEngineSampler::Create("LINEAR", Desc);
	}

	{
		D3D11_BLEND_DESC Desc = {};

		Desc.AlphaToCoverageEnable = false;
		Desc.IndependentBlendEnable = false;
		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

		UEngineBlend::Create("EngineBase", Desc);
	}

	{
		D3D11_BLEND_DESC Desc = {};
		Desc.AlphaToCoverageEnable = false;
		Desc.IndependentBlendEnable = false;
		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

		UEngineBlend::Create("Overlay", Desc);
	}
}

void MaterialInit()
{
	std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("2DImage");
	Mat->SetPixelShader("ImageShader.fx");
	Mat->SetVertexShader("ImageShader.fx");
}

void EngineTextureInit()
{
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
		
		for (UEngineFile& File : Files)
		{
			UEngineTexture::Load(File.GetFullPath());
		}
	}
}

void UEngineGraphicDevice::EngineResourcesInit()
{
	MeshInit();
	ShaderInit();
	SettingInit();
	MaterialInit();
	EngineTextureInit();
}

void UEngineGraphicDevice::EngineResourcesRelease()
{
	UEngineSound::ResourcesRelease();
	UEngineTexture::ResourcesRelease();

	UEngineVertexBuffer::ResourcesRelease();
	UEngineIndexBuffer::ResourcesRelease();
	UEngineMesh::ResourcesRelease();

	UEngineVertexShader::ResourcesRelease();
	UEnginePixelShader::ResourcesRelease();
	UEngineRasterizer::ResourcesRelease();
	UEngineBlend::ResourcesRelease();
	UEngineMaterial::ResourcesRelease();
}
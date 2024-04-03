#include "PreCompile.h"
#include "EngineGraphicDevice.h"

#include "EngineTexture.h"
#include "EngineVertex.h"
#include "EngineMesh.h"
#include "EngineVertexShader.h"
#include "EnginePixelShader.h"
#include "EngineRasterizer.h"
#include "EngineMaterial.h"

void MeshInit()
{
	{
		std::vector<FEngineVertex> VertexData;
		VertexData.resize(4);
		VertexData[0] = { {-0.5f, 0.5f, 0.0f, 1.0f} };
		VertexData[1] = { {0.5f, 0.5f, 0.0f, 1.0f} };
		VertexData[2] = { {0.5f, -0.5f, 0.0f, 1.0f} };
		VertexData[3] = { {-0.5f, -0.5f, 0.0f, 1.0f} };

		std::shared_ptr<UEngineVertexBuffer> VertexBuffer = UEngineVertexBuffer::Create("Rect", VertexData);

		std::vector<UINT> IndexData = { 0, 1, 2, 0, 2, 3 };
		std::shared_ptr<UEngineIndexBuffer> IndexBuffer = UEngineIndexBuffer::Create("Rect", IndexData);

		UEngineMesh::Create("Rect");
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
	D3D11_RASTERIZER_DESC Desc = {};
	Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
	Desc.DepthClipEnable = TRUE;
	Desc.AntialiasedLineEnable = TRUE;

	UEngineRasterizer::Create("EngineBasic", Desc);

	std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("2DImage");
	Mat->SetPixelShader("ImageShader.fx");
	Mat->SetVertexShader("ImageShader.fx");
	Mat->SetRasterizer("EngineBasic");
}

void MaterialInit()
{

}

void UEngineGraphicDevice::EngineResourcesInit()
{
	MeshInit();
	ShaderInit();
	SettingInit();
	MaterialInit();
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
	UEngineMaterial::ResourcesRelease();
}
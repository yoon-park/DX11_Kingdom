#include "PreCompile.h"
#include "EngineGraphicDevice.h"

#include "EngineVertex.h"
#include "EngineMesh.h"
#include "EngineTexture.h"

void UEngineGraphicDevice::EngineResourcesInit()
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

void UEngineGraphicDevice::EngineResourcesRelease()
{
	UEngineSound::ResourcesRelease();
	UEngineTexture::ResourcesRelease();
	UEngineVertexBuffer::ResourcesRelease();
	UEngineIndexBuffer::ResourcesRelease();
	UEngineMesh::ResourcesRelease();
}
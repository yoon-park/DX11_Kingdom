#pragma once
#include "SceneComponent.h"

#include "EngineInputLayout.h"
#include "EngineMesh.h"
#include "EngineMaterial.h"
#include "EngineShaderResources.h"
#include "Camera.h"

class UEngineShaderResources;

class URenderer : public USceneComponent, public std::enable_shared_from_this<URenderer>
{
	GENERATED_BODY(USceneComponent)

	friend ULevel;

public:
	URenderer();
	~URenderer();

	URenderer(const URenderer& _Other) = delete;
	URenderer(URenderer&& _Other) noexcept = delete;
	URenderer& operator=(const URenderer& _Other) = delete;
	URenderer& operator=(URenderer&& _Other) noexcept = delete;

	std::shared_ptr<UEngineShaderResources> Resources;

	void SetMesh(std::string_view _Name);
	void SetMaterial(std::string_view _Name);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void ResCopy();

private:
	std::shared_ptr<UEngineInputLayout> Layout;
	std::shared_ptr<UEngineMesh> Mesh;
	std::shared_ptr<UEngineMaterial> Material;

	void RenderingTransformUpdate(std::shared_ptr<UCamera> _Camera);
	void Render(float _DeltaTime);
};
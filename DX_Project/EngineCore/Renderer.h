#pragma once
#include "SceneComponent.h"

#include "EngineMesh.h"
#include "EngineMaterial.h"

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

	void SetMesh(std::string_view _Name);
	void SetMaterial(std::string_view _Name);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<UEngineMesh> Mesh;
	std::shared_ptr<UEngineMaterial> Material;

	void Render(float _DeltaTime);
};
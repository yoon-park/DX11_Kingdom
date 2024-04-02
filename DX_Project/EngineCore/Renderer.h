#pragma once
#include "SceneComponent.h"

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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void Render(float _DeltaTime);
};
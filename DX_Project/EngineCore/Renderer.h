#pragma once
#include "SceneComponent.h"

class URenderer : public USceneComponent
{
	GENERATED_BODY(USceneComponent)

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

};
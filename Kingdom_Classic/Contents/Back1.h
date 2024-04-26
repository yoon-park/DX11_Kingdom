#pragma once
#include "KingdomActor.h"

class USpriteRenderer;

class ABack1 : public AKingdomActor
{
	GENERATED_BODY(AKingdomActor)

public:
	ABack1();
	~ABack1();

	ABack1(const ABack1& _Other) = delete;
	ABack1(ABack1&& _Other) noexcept = delete;
	ABack1& operator=(const ABack1& _Other) = delete;
	ABack1& operator=(ABack1&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;
	float4 Color;
};
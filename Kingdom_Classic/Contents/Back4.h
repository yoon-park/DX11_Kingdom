#pragma once
#include "KingdomActor.h"

class USpriteRenderer;

class ABack4 : public AKingdomActor
{
	GENERATED_BODY(AKingdomActor)

public:
	ABack4();
	~ABack4();

	ABack4(const ABack4& _Other) = delete;
	ABack4(ABack4&& _Other) noexcept = delete;
	ABack4& operator=(const ABack4& _Other) = delete;
	ABack4& operator=(ABack4&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;
	float4 Color;
};
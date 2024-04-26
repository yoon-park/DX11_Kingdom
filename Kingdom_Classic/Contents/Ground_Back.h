#pragma once
#include "KingdomActor.h"

class USpriteRenderer;

class AGround_Back : public AKingdomActor
{
	GENERATED_BODY(AKingdomActor)

public:
	AGround_Back();
	~AGround_Back();

	AGround_Back(const AGround_Back& _Other) = delete;
	AGround_Back(AGround_Back&& _Other) noexcept = delete;
	AGround_Back& operator=(const AGround_Back& _Other) = delete;
	AGround_Back& operator=(AGround_Back&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;
	float4 Color;
};
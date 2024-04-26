#pragma once
#include "KingdomActor.h"

class USpriteRenderer;

class ASky : public AKingdomActor
{
	GENERATED_BODY(AKingdomActor)

public:
	ASky();
	~ASky();

	ASky(const ASky& _Other) = delete;
	ASky(ASky&& _Other) noexcept = delete;
	ASky& operator=(const ASky& _Other) = delete;
	ASky& operator=(ASky&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;
	float4 Color;
};
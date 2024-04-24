#pragma once
#include "Spot.h"

class AWall : public ASpot
{
	GENERATED_BODY(ASpot)

public:
	AWall();
	~AWall();

	AWall(const AWall& _Other) = delete;
	AWall(AWall&& _Other) noexcept = delete;
	AWall& operator=(const AWall& _Other) = delete;
	AWall& operator=(AWall&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;

	void Upgrade() override;
};
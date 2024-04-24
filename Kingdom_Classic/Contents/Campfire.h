#pragma once
#include "Spot.h"

class ACampfire : public ASpot
{
	GENERATED_BODY(ASpot)

public:
	ACampfire();
	~ACampfire();

	ACampfire(const ACampfire& _Other) = delete;
	ACampfire(ACampfire&& _Other) noexcept = delete;
	ACampfire& operator=(const ACampfire& _Other) = delete;
	ACampfire& operator=(ACampfire&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;

	void Upgrade() override;
};
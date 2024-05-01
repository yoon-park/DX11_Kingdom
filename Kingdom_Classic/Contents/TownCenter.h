#pragma once
#include "Spot.h"

class ATownCenter : public ASpot
{
	GENERATED_BODY(ASpot)

public:
	ATownCenter();
	~ATownCenter();

	ATownCenter(const ATownCenter& _Other) = delete;
	ATownCenter(ATownCenter&& _Other) noexcept = delete;
	ATownCenter& operator=(const ATownCenter& _Other) = delete;
	ATownCenter& operator=(ATownCenter&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer_Castle;
	USpriteRenderer* Renderer_Campfire;

	void SetCoinIndicatorLocation() override;
	void SettingUpgrade() override;
};
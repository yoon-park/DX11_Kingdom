#pragma once
#include "Spot.h"

class ATower : public ASpot
{
	GENERATED_BODY(ASpot)

public:
	ATower();
	~ATower();

	ATower(const ATower& _Other) = delete;
	ATower(ATower&& _Other) noexcept = delete;
	ATower& operator=(const ATower& _Other) = delete;
	ATower& operator=(ATower&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;

	void SetCoinIndicator() override;
	void Upgrade() override;
};
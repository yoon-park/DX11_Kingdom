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

	void SetDir(EEngineDir _Dir);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;

	void SetCoinIndicatorLocation() override;
	void SettingUpgrade() override;

	// State
	void ActiveStart() override;
	void ActiveEnd() override;
};
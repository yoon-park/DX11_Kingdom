#pragma once
#include "Spot.h"

#include "Wall.h"
#include "Tower.h"
#include "BowVendor.h"
#include "HammerVendor.h"

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
	USpriteRenderer* Renderer_Campfire;
	USpriteRenderer* Renderer_Banner;
	USpriteRenderer* Renderer_Castle;
	std::vector<USpriteRenderer*> Renderer_Walls;

	std::shared_ptr<AWall> InnerWall_L;
	std::shared_ptr<AWall> InnerWall_R;
	std::shared_ptr<ATower> Tower_L;
	std::shared_ptr<ATower> Tower_R;
	std::shared_ptr<AWall> OuterWall_L;
	std::shared_ptr<AWall> OuterWall_R;
	std::shared_ptr<ABowVendor> BowVendor;
	std::shared_ptr<AHammerVendor> HammerVendor;

	void SetCoinIndicatorLocation() override;
	void SettingUpgrade() override;
	void CheckIsUpdatable();

	// State
	void ActiveStart() override;
	void ActiveEnd() override;
};
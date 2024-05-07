#pragma once
#include "Spot.h"

#include "Wall.h"

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

	void SetCoinIndicatorLocation() override;
	void SettingUpgrade() override;
};
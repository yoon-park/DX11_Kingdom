#pragma once
#include "MovingActor.h"

class ACoin : public AMovingActor
{
	GENERATED_BODY(AMovingActor)

public:
	ACoin();
	~ACoin();

	ACoin(const ACoin& _Other) = delete;
	ACoin(ACoin&& _Other) noexcept = delete;
	ACoin& operator=(const ACoin& _Other) = delete;
	ACoin& operator=(ACoin&& _Other) noexcept = delete;

	UStateManager State;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;
	UCollision* Collision;
	AMovingActor* AbsorbOwner = nullptr;
	float Alpha = 1.0f;

	void CheckGround() override;
	void CheckAbsorb();

	// State
	void StateInit();

	void IdleStart();
	void PaySpotStart();
	void PayGroundStart();
	void FallStart();

	void Idle(float _DeltaTime);
	void PaySpot(float _DeltaTime);
	void PayGround(float _DeltaTime);
	void Wait(float _DeltaTime);
	void Fall(float _DeltaTime);
	void Disappear(float _DeltaTime);
	void Absorb(float _DeltaTime);
};
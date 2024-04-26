#pragma once
#include "KingdomActor.h"
#include "Spot.h"

class APlayer : public AKingdomActor
{
	GENERATED_BODY(AKingdomActor)

public:
	APlayer();
	~APlayer();

	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	UStateManager State;

	bool GetIsPaying()
	{
		return IsPaying;
	}

	ASpot* GetCurSpot()
	{
		return CurSpot;
	}

	void SetIsPaying(bool _IsPaying)
	{
		IsPaying = _IsPaying;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer_Player;
	USpriteRenderer* Renderer_Horse;
	UCollision* Collision_Player;
	UCollision* Collision_Horse_Front;

	EEngineDir PrevDir = EEngineDir::Right;
	EEngineDir CurDir = EEngineDir::Right;
	float Speed = 0.0f;
	bool IsPaying = false;
	ASpot* CurSpot = nullptr;
	
	bool IsGround() override;
	void CheckSpot();
	void ChangeDir(EEngineDir _Dir) override;

	void DebugMessageFunction(float _Delta);

	// State
	void StateInit();

	void IdleStart();
	void WalkStart();
	void RunStart();
	void RearStart();
	void EatStart();
	void PayStart();

	void Idle(float _DeltaTime);
	void Walk(float _DeltaTime);
	void Run(float _DeltaTime);
	void Rear(float _DeltaTime);
	void Eat(float _DeltaTime);
	void Pay(float _DeltaTime);

	void PayEnd();
};
#pragma once
#include "KingdomActor.h"
#include "Spot.h"
#include "Coin.h"

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

	bool GetIsPayDone()
	{
		return IsPayDone;
	}

	ASpot* GetCurSpot()
	{
		return CurSpot;
	}

	ACoin* GetCurCoin()
	{
		return CurCoin;
	}

	int GetCurCoinCnt()
	{
		return CurCoinCnt;
	}

	void SetIsPaying(bool _IsPaying)
	{
		IsPaying = _IsPaying;
	}

	void SetIsPayDone(bool _IsPayDone)
	{
		IsPayDone = _IsPayDone;
	}

	void ResetCurCoin()
	{
		CurCoin = nullptr;
		CurCoinCnt = -1;
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
	bool IsPayDone = false;
	bool IsGround = false;
	EGroundType CurGroundType = EGroundType::Plain;
	ASpot* CurSpot = nullptr;
	ACoin* CurCoin = nullptr;
	int CurCoinCnt = -1;
	int CurLeftCoin = 0;

	void ChangeDir(EEngineDir _Dir) override;
	void CheckGround() override;
	void CheckSpot();
	void CreateCoin();

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
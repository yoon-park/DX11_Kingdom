#pragma once
#include "MovingActor.h"
#include "Spot.h"
#include "Coin.h"

class APlayer : public AMovingActor
{
	GENERATED_BODY(AMovingActor)

public:
	APlayer();
	~APlayer();

	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	UStateManager State;

	int GetCoinNum()
	{
		return CoinNum;
	}

	bool GetIsPaying()
	{
		return IsPaying;
	}

	ASpot* GetCurSpot()
	{
		return CurSpot;
	}

	ACoin* GetCurCoin()
	{
		return CurCoin;
	}

	int GetCurCoinIndex()
	{
		return CurCoinIndex;
	}

	void SetIsPaying(bool _IsPaying)
	{
		IsPaying = _IsPaying;
	}

	void AddCoin()
	{
		CoinNum += 1;
	}

	void SubCoin()
	{
		CoinNum -= 1;
	}

	void ResetCurCoin()
	{
		CurCoin = nullptr;
		CurCoinIndex = -1;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer_Player;
	USpriteRenderer* Renderer_Horse;
	UCollision* Collision_Player;
	UCollision* Collision_Horse_Front;

	int CoinNum = 10;
	bool IsPaying = false;
	ASpot* CurSpot = nullptr;
	ACoin* CurCoin = nullptr;
	int CurCoinIndex = -1;

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
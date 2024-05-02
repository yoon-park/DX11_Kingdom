#pragma once
#include "MovingActor.h"

class ANPC : public AMovingActor
{
	GENERATED_BODY(AMovingActor)

public:
	ANPC();
	~ANPC();

	ANPC(const ANPC& _Other) = delete;
	ANPC(ANPC&& _Other) noexcept = delete;
	ANPC& operator=(const ANPC& _Other) = delete;
	ANPC& operator=(ANPC&& _Other) noexcept = delete;

	UStateManager State;

	int GetCoinNum()
	{
		return CoinNum;
	}

	void AddCoin()
	{
		CoinNum += 1;
	}

	void SubCoin()
	{
		CoinNum -= 1;
	}

protected:
	USpriteRenderer* Renderer;
	UCollision* Collision;

	int CoinNum = 0;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void ChangeDir(EEngineDir _Dir);

private:

};
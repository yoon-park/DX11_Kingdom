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

protected:
	USpriteRenderer* Renderer;
	UCollision* Collision;

	int CoinNum = 0;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void ChangeDir(EEngineDir _Dir);

private:
	// State
	void StateInit();
	
	void Vagrant_IdleStart();
	void Vagrant_WalkStart();
	void Vagrant_RunStart();
	void Villager_IdleStart();
	void Villager_WalkStart();
	void Villager_RunStart();
	void Villager_BumpedStart();
	void Villager_GetupStart();
	void Archer_IdleStart();
	void Archer_WalkStart();
	void Archer_RunStart();
	void Archer_PrepStart();
	void Archer_ShootStart();
	void Builder_IdleStart();
	void Builder_WalkStart();
	void Builder_RunStart();
	void Builder_WorkStart();

	void Vagrant_Idle(float _DeltaTime);
	void Vagrant_Walk(float _DeltaTime);
	void Vagrant_Run(float _DeltaTime);
	void Villager_Idle(float _DeltaTime);
	void Villager_Walk(float _DeltaTime);
	void Villager_Run(float _DeltaTime);
	void Villager_Bumped(float _DeltaTime);
	void Villager_Getup(float _DeltaTime);
	void Archer_Idle(float _DeltaTime);
	void Archer_Walk(float _DeltaTime);
	void Archer_Run(float _DeltaTime);
	void Archer_Prep(float _DeltaTime);
	void Archer_Shoot(float _DeltaTime);
	void Builder_Idle(float _DeltaTime);
	void Builder_Walk(float _DeltaTime);
	void Builder_Run(float _DeltaTime);
	void Builder_Work(float _DeltaTime);
};
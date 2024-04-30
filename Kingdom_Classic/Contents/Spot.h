#pragma once
#include "KingdomActor.h"

class ASpot : public AActor
{
	GENERATED_BODY(AActor)

public:
	ASpot();
	~ASpot();

	ASpot(const ASpot& _Other) = delete;
	ASpot(ASpot&& _Other) noexcept = delete;
	ASpot& operator=(const ASpot& _Other) = delete;
	ASpot& operator=(ASpot&& _Other) noexcept = delete;

	FVector GetCoinLocation(int _Index)
	{
		FVector Location = GetActorLocation() + Renderer_Coins[_Index]->GetLocalPosition();
		return Location;
	}

	bool GetIsUpdateDone()
	{
		return IsUpdateDone;
	}

	int GetLeftCoin()
	{
		return LeftCoin;
	}

	void SetIsUpdateDone(bool _IsUpdateDone)
	{
		IsUpdateDone = _IsUpdateDone;
	}

protected:
	UDefaultSceneComponent* Root;
	ESpotUpgrade CurTier = ESpotUpgrade::Tier0;
	bool IsUpgradable = true;
	bool IsUpdateDone = false;
	int RequiredCoin = 1;
	int LeftCoin = RequiredCoin;
	UCollision* Collision_Update;

	std::vector<USpriteRenderer*> Renderer_Coins;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CheckPlayer();
	void CheckLeftCoin();
	virtual void Upgrade();

private:

};
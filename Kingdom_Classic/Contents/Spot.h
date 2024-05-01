#pragma once
#include "KingdomActor.h"

class ASpot : public AKingdomActor
{
	GENERATED_BODY(AKingdomActor)

public:
	ASpot();
	~ASpot();

	ASpot(const ASpot& _Other) = delete;
	ASpot(ASpot&& _Other) noexcept = delete;
	ASpot& operator=(const ASpot& _Other) = delete;
	ASpot& operator=(ASpot&& _Other) noexcept = delete;

	FVector GetCoinLocation(int _Index)
	{
		return Renderer_Coins[_Index]->GetWorldPosition();
	}

	bool GetIsUpgradable()
	{
		return IsUpgradable;
	}

	int GetRequiredCoin()
	{
		return RequiredCoin;
	}

	int GetLeftCoin()
	{
		return LeftCoin;
	}

	void SetCoinIndicator();

protected:
	UDefaultSceneComponent* Root;
	ESpotUpgrade CurTier = ESpotUpgrade::Tier0;
	bool IsPlayerContact = false;
	bool IsUpgradable = true;
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
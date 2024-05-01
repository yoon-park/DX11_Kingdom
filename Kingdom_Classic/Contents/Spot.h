#pragma once

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

	UStateManager State;

	ESpotUpgrade GetCurTier()
	{
		return CurTier;
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

	FVector GetCoinLocation(int _Index)
	{
		return Renderer_Coins[_Index]->GetWorldPosition();
	}

protected:
	UDefaultSceneComponent* Root;
	UCollision* Collision_Update;

	ESpotUpgrade CurTier = ESpotUpgrade::Tier0;
	bool IsPlayerContact = false;
	bool IsUpgradable = true;
	bool SkipUpgradeProgress = false;
	int RequiredCoin = 1;
	int LeftCoin = RequiredCoin;

	std::vector<USpriteRenderer*> Renderer_Coins;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CheckPlayer();
	void CheckLeftCoin();

	void SetCoinIndicatorActive(bool _Active, int _CoinNum = 12);
	virtual void SetCoinIndicatorLocation() {};
	virtual void SettingUpgrade() {};

	// State
	virtual void StateInit();

	virtual void InactiveIdleStart();
	virtual void ActiveIdleStart();
	virtual void UpgradeStart();
	virtual void UpgradeDoneStart();

	virtual void InactiveIdle(float _DeltaTime);
	virtual void ActiveIdle(float _DeltaTime);
	virtual void Upgrade(float _DeltaTime);
	virtual void UpgradeDone(float _DeltaTime);

private:
};
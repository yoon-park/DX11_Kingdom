#pragma once
#include "BuildingObject.h"

class ASpot : public ABuildingObject
{
	GENERATED_BODY(ABuildingObject)

public:
	ASpot();
	~ASpot();

	ASpot(const ASpot& _Other) = delete;
	ASpot(ASpot&& _Other) noexcept = delete;
	ASpot& operator=(const ASpot& _Other) = delete;
	ASpot& operator=(ASpot&& _Other) noexcept = delete;

	ESpotUpgrade GetCurTier()
	{
		return CurTier;
	}

	bool GetIsUpgradable()
	{
		return IsUpgradable;
	}

	void SetIsUpgradable(bool _IsUpgradable)
	{
		IsUpgradable = _IsUpgradable;
	}

protected:
	ESpotUpgrade CurTier = ESpotUpgrade::Tier0;
	bool IsUpgradable = true;
	bool SkipUpgradeProgress = false;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	virtual void SettingUpgrade() {};

	// State
	void StateInit();

	void InactiveStart();
	virtual void ActiveStart();
	void UpgradeStart();
	void UpgradeDoneStart();

	void Inactive(float _DeltaTime);
	void Active(float _DeltaTime);
	void Upgrade(float _DeltaTime);
	void UpgradeDone(float _DeltaTime);

	virtual void ActiveEnd();

private:

};
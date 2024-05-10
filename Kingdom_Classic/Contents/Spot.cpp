#include "PreCompile.h"
#include "Spot.h"

#include "PlayGameMode.h"
#include "Player.h"

ASpot::ASpot()
{
	{
		for (int i = 0; i < 12; i++)
		{
			USpriteRenderer* Coin = CreateDefaultSubObject<USpriteRenderer>("Renderer");
			Coin->SetupAttachment(Root);
			Coin->SetActive(false);
			Renderer_Coins.push_back(Coin);
		}
	}
	{
		Collision_Check = CreateDefaultSubObject<UCollision>("Collision_Update");
		Collision_Check->SetupAttachment(Root);
		Collision_Check->SetScale(FVector(80.0f, 80.0f, 100.0f));
		Collision_Check->SetPosition(FVector(0.0f, -24.0f, 0.0f));
		Collision_Check->SetCollisionGroup(ECollisionOrder::BuildingObject);
		Collision_Check->SetCollisionType(ECollisionType::Rect);
	}

	Type = EBuildingObjectType::Spot;
}

ASpot::~ASpot()
{

}

void ASpot::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < 12; i++)
	{
		Renderer_Coins[i]->SetSprite("Coin_Indicator.png");
		Renderer_Coins[i]->SetAutoSize(1.0f, true);
		Renderer_Coins[i]->SetOrder(ERenderOrder::UI);
	}

	SetCoinIndicatorLocation();
	StateInit();
}

void ASpot::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void ASpot::StateInit()
{
	{
		State.CreateState("Inactive");
		State.SetStartFunction("Inactive", std::bind(&ASpot::InactiveStart, this));
		State.SetUpdateFunction("Inactive", std::bind(&ASpot::Inactive, this, std::placeholders::_1));

		State.CreateState("Active");
		State.SetStartFunction("Active", std::bind(&ASpot::ActiveStart, this));
		State.SetUpdateFunction("Active", std::bind(&ASpot::Active, this, std::placeholders::_1));
		State.SetEndFunction("Active", std::bind(&ASpot::ActiveEnd, this));

		State.CreateState("Upgrade");
		State.SetStartFunction("Upgrade", std::bind(&ASpot::UpgradeStart, this));
		State.SetUpdateFunction("Upgrade", std::bind(&ASpot::Upgrade, this, std::placeholders::_1));

		State.CreateState("UpgradeDone");
		State.SetStartFunction("UpgradeDone", std::bind(&ASpot::UpgradeDoneStart, this));
		State.SetUpdateFunction("UpgradeDone", std::bind(&ASpot::UpgradeDone, this, std::placeholders::_1));
	}

	State.ChangeState("Inactive");
}

void ASpot::InactiveStart()
{
	SetCoinIndicatorActive(false, 12);
}

void ASpot::ActiveStart()
{
	SetCoinIndicatorActive(true, RequiredCoin);
}

void ASpot::UpgradeStart()
{

}

void ASpot::UpgradeDoneStart()
{
	SettingUpgrade();
	SetCoinIndicatorLocation();

	LeftCoin = RequiredCoin;
}

void ASpot::Inactive(float _DeltaTime)
{
	if (IsPlayerContact == true && IsUpgradable == true)
	{
		State.ChangeState("Active");
		return;
	}

	CheckPlayer();
}

void ASpot::Active(float _DeltaTime)
{
	if (IsPlayerContact == false)
	{
		State.ChangeState("Inactive");
		return;
	}

	if (LeftCoin == 0 && IsUpgradable == true)
	{
		if (SkipUpgradeProgress == true)
		{
			State.ChangeState("UpgradeDone");
			return;
		}

		State.ChangeState("Upgrade");
		return;
	}

	CheckPlayer();
	CheckLeftCoin();
}

void ASpot::Upgrade(float _DeltaTime)
{
	State.ChangeState("UpgradeDone");
	return;
}

void ASpot::UpgradeDone(float _DeltaTime)
{
	State.ChangeState("Inactive");
	return;
}

void ASpot::ActiveEnd()
{

}
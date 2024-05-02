#include "PreCompile.h"
#include "Spot.h"

#include "PlayGameMode.h"
#include "Player.h"

ASpot::ASpot()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	for (int i = 0; i < 12; i++)
	{
		USpriteRenderer* Coin = CreateDefaultSubObject<USpriteRenderer>("Renderer");
		Coin->SetupAttachment(Root);
		Coin->SetActive(false);
		Renderer_Coins.push_back(Coin);
	}

	Collision_Update = CreateDefaultSubObject<UCollision>("Collision_Update");
	Collision_Update->SetupAttachment(Root);
	Collision_Update->SetScale(FVector(80.0f, 80.0f, 100.0f));
	Collision_Update->AddPosition(FVector(0.0f, -24.0f, 0.0f));
	Collision_Update->SetCollisionGroup(ECollisionOrder::Spot);
	Collision_Update->SetCollisionType(ECollisionType::Rect);

	SetRoot(Root);
}

ASpot::~ASpot()
{

}

void ASpot::SetCoinIndicatorActive(bool _Active, int CoinNum)
{
	if (_Active == true)
	{
		for (int i = 0; i < CoinNum; i++)
		{
			Renderer_Coins[i]->SetActive(true);
		}
	}
	else
	{
		for (int i = 0; i < CoinNum; i++)
		{
			Renderer_Coins[i]->SetActive(false);
		}
	}
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

	StateInit();
	SetCoinIndicatorLocation();
}

void ASpot::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void ASpot::CheckPlayer()
{
	Collision_Update->CollisionStay(ECollisionOrder::Horse, [=](std::shared_ptr<UCollision> _Collision)
		{
			IsPlayerContact = true;
			SetCoinIndicatorActive(true, RequiredCoin);
			return;
		}
	);

	Collision_Update->CollisionExit(ECollisionOrder::Horse, [=](std::shared_ptr<UCollision> _Collision)
		{
			IsPlayerContact = false;
			SetCoinIndicatorActive(false);
			return;
		}
	);
}

void ASpot::CheckLeftCoin()
{
	if (
		IsPlayerContact == false ||
		APlayGameMode::MainPlayer->GetIsPaying() == false
		)
	{
		LeftCoin = RequiredCoin;
	}
	else if (
		IsPlayerContact == true &&
		APlayGameMode::MainPlayer->GetIsPaying() == true &&
		APlayGameMode::MainPlayer->GetCurCoin()->State.GetCurStateName() == "Wait"
		)
	{
		LeftCoin -= 1;
	}
}

void ASpot::StateInit()
{
	{
		State.CreateState("InactiveIdle");
		State.SetStartFunction("InactiveIdle", std::bind(&ASpot::InactiveIdleStart, this));
		State.SetUpdateFunction("InactiveIdle", std::bind(&ASpot::InactiveIdle, this, std::placeholders::_1));

		State.CreateState("ActiveIdle");
		State.SetStartFunction("ActiveIdle", std::bind(&ASpot::ActiveIdleStart, this));
		State.SetUpdateFunction("ActiveIdle", std::bind(&ASpot::ActiveIdle, this, std::placeholders::_1));

		State.CreateState("Upgrade");
		State.SetStartFunction("Upgrade", std::bind(&ASpot::UpgradeStart, this));
		State.SetUpdateFunction("Upgrade", std::bind(&ASpot::Upgrade, this, std::placeholders::_1));

		State.CreateState("UpgradeDone");
		State.SetStartFunction("UpgradeDone", std::bind(&ASpot::UpgradeDoneStart, this));
		State.SetUpdateFunction("UpgradeDone", std::bind(&ASpot::UpgradeDone, this, std::placeholders::_1));
	}

	State.ChangeState("InactiveIdle");
}

void ASpot::InactiveIdleStart()
{
	SetCoinIndicatorActive(false);
}

void ASpot::ActiveIdleStart()
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

void ASpot::InactiveIdle(float _DeltaTime)
{
	if (IsPlayerContact == true && IsUpgradable == true)
	{
		State.ChangeState("ActiveIdle");
		return;
	}

	CheckPlayer();
}

void ASpot::ActiveIdle(float _DeltaTime)
{
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
	State.ChangeState("InactiveIdle");
	return;
}
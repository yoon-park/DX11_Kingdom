#include "PreCompile.h"
#include "Tower.h"

ATower::ATower()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
}

ATower::~ATower()
{

}

void ATower::SetDir(EEngineDir _Dir)
{
	Renderer->SetDir(_Dir);
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Tower_0.png");
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderOrder::Building);
}

void ATower::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ATower::SetCoinIndicatorLocation()
{
	switch (RequiredCoin)
	{
	case 1:
	{
		Renderer_Coins[0]->SetPosition({ 0.0f, 40.0f, 0.0f, 0.0f });
		break;
	}
	case 3:
	{
		Renderer_Coins[0]->SetPosition({ -15.0f, 40.0f, 0.0f, 0.0f });
		Renderer_Coins[1]->SetPosition({ 0.0f, 40.0f, 0.0f, 0.0f });
		Renderer_Coins[2]->SetPosition({ 15.0f, 40.0f, 0.0f, 0.0f });
		break;
	}
	case 6:
	{
		Renderer_Coins[0]->SetPosition({ -15.0f, 40.0f, 0.0f, 0.0f });
		Renderer_Coins[1]->SetPosition({ 0.0f, 40.0f, 0.0f, 0.0f });
		Renderer_Coins[2]->SetPosition({ 15.0f, 40.0f, 0.0f, 0.0f });
		Renderer_Coins[3]->SetPosition({ -15.0f, 55.0f, 0.0f, 0.0f });
		Renderer_Coins[4]->SetPosition({ 0.0f, 55.0f, 0.0f, 0.0f });
		Renderer_Coins[5]->SetPosition({ 15.0f, 55.0f, 0.0f, 0.0f });
		break;
	}
	case 9:
	{
		Renderer_Coins[0]->SetPosition({ -23.0f, 40.0f, 0.0f, 0.0f });
		Renderer_Coins[1]->SetPosition({ -8.0f, 40.0f, 0.0f, 0.0f });
		Renderer_Coins[2]->SetPosition({ 8.0f, 40.0f, 0.0f, 0.0f });
		Renderer_Coins[3]->SetPosition({ 23.0f, 40.0f, 0.0f, 0.0f });
		Renderer_Coins[4]->SetPosition({ -30.0f, 55.0f, 0.0f, 0.0f });
		Renderer_Coins[5]->SetPosition({ -15.0f, 55.0f, 0.0f, 0.0f });
		Renderer_Coins[6]->SetPosition({ 0.0f, 55.0f, 0.0f, 0.0f });
		Renderer_Coins[7]->SetPosition({ 15.0f, 55.0f, 0.0f, 0.0f });
		Renderer_Coins[8]->SetPosition({ 30.0f, 55.0f, 0.0f, 0.0f });
		break;
	}
	default:
		break;
	}
}

void ATower::SettingUpgrade()
{
	switch (CurTier)
	{
	case ESpotUpgrade::Tier0:
	{
		CurTier = ESpotUpgrade::Tier1;
		Renderer->SetSprite("Tower_1.png");
		RequiredCoin = 3;
		break;
	}
	case ESpotUpgrade::Tier1:
	{
		CurTier = ESpotUpgrade::Tier2;
		Renderer->SetSprite("Tower_2.png");
		RequiredCoin = 6;
		break;
	}
	case ESpotUpgrade::Tier2:
	{
		CurTier = ESpotUpgrade::Tier3;
		Renderer->SetSprite("Tower_3.png");
		RequiredCoin = 0;
		IsUpgradable = false;
		break;
	}
	default:
		break;
	}
}

void ATower::ActiveStart()
{
	Super::ActiveStart();

	Renderer->SetPlusColor({ 0.1f, 0.1f, 0.0f, 1.0f });
}

void ATower::ActiveEnd()
{
	Super::ActiveEnd();

	Renderer->SetPlusColor({ 0.0f, 0.0f, 0.0f, 0.0f });
}
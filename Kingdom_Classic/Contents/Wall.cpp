#include "PreCompile.h"
#include "Wall.h"

AWall::AWall()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
}

AWall::~AWall()
{

}

void AWall::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Wall_0.png");
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderOrder::GroundObject);
}

void AWall::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AWall::SetDir(EEngineDir _Dir)
{
	Renderer->SetDir(_Dir);
}

void AWall::SetCoinIndicatorLocation()
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

void AWall::SettingUpgrade()
{
	switch (CurTier)
	{
	case ESpotUpgrade::Tier0:
	{
		CurTier = ESpotUpgrade::Tier1;
		Renderer->SetSprite("Wall_1.png");
		RequiredCoin = 3;
		break;
	}
	case ESpotUpgrade::Tier1:
	{
		CurTier = ESpotUpgrade::Tier2;
		Renderer->SetSprite("Wall_2.png");
		RequiredCoin = 6;
		break;
	}
	case ESpotUpgrade::Tier2:
	{
		CurTier = ESpotUpgrade::Tier3;
		Renderer->SetSprite("Wall_3.png");
		RequiredCoin = 0;
		IsUpgradable = false;
		break;
	}
	default:
		break;
	}
}
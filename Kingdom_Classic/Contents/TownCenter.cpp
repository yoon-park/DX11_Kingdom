#include "PreCompile.h"
#include "TownCenter.h"

ATownCenter::ATownCenter()
{
	Renderer_Castle = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer_Castle->SetupAttachment(Root);

	Renderer_Campfire = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer_Campfire->SetupAttachment(Root);

	Renderer_Coin00 = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer_Coin00->SetupAttachment(Root);

	SetRoot(Root);
}

ATownCenter::~ATownCenter()
{

}

void ATownCenter::BeginPlay()
{
	Super::BeginPlay();

	Renderer_Castle->SetSprite("TownCenter_00.png");
	Renderer_Castle->SetAutoSize(1.0f, true);
	Renderer_Castle->SetOrder(ERenderOrder::BackObject);

	Renderer_Campfire->SetSprite("Campfire_00.png");
	Renderer_Campfire->SetAutoSize(1.0f, true);
	Renderer_Campfire->AddPosition({ 0.0f, -35.0f, 0.0f, 0.0f });
	Renderer_Campfire->SetOrder(ERenderOrder::GroundObject);

	Renderer_Coin00->SetSprite("coin_indicator.png");
	Renderer_Coin00->SetAutoSize(1.0f, true);
	Renderer_Coin00->AddPosition({ 0.0f, 0.0f, 0.0f, 0.0f });
	Renderer_Coin00->SetOrder(ERenderOrder::UI);
}

void ATownCenter::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ATownCenter::Upgrade()
{
	switch (CurTier)
	{
	case ESpotUpgrade::Tier0:
	{
		CurTier = ESpotUpgrade::Tier1;
		Renderer_Campfire->SetSprite("Campfire_01.png");
		break;
	}
	case ESpotUpgrade::Tier1:
	{
		CurTier = ESpotUpgrade::Tier2;
		Renderer_Castle->SetSprite("TownCenter_02.png");
		Renderer_Campfire->SetSprite("Campfire_02.png");
		break;
	}
	case ESpotUpgrade::Tier2:
	{
		CurTier = ESpotUpgrade::Tier3;
		Renderer_Castle->SetSprite("TownCenter_03.png");
		Renderer_Campfire->SetSprite("Campfire_03.png");
		break;
	}
	case ESpotUpgrade::Tier3:
	{
		CurTier = ESpotUpgrade::Tier4;
		Renderer_Castle->SetSprite("TownCenter_04.png");
		break;
	}
	default:
		break;
	}
}
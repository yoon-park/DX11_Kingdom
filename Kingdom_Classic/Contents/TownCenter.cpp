#include "PreCompile.h"
#include "TownCenter.h"

ATownCenter::ATownCenter()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);

	SetRoot(Root);
}

ATownCenter::~ATownCenter()
{

}

void ATownCenter::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("TownCenter_00.png");
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderOrder::BackObject);
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
		break;
	}
	case ESpotUpgrade::Tier1:
	{
		CurTier = ESpotUpgrade::Tier2;
		Renderer->SetSprite("TownCenter_02.png");
		break;
	}
	case ESpotUpgrade::Tier2:
	{
		CurTier = ESpotUpgrade::Tier3;
		Renderer->SetSprite("TownCenter_03.png");
		break;
	}
	case ESpotUpgrade::Tier3:
	{
		CurTier = ESpotUpgrade::Tier4;
		Renderer->SetSprite("TownCenter_04.png");
		break;
	}
	default:
		break;
	}
}
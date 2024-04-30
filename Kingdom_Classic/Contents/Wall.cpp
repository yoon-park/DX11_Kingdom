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

	Renderer->SetSprite("wall_0.png");
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderOrder::GroundObject);
}

void AWall::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AWall::Upgrade()
{
	switch (CurTier)
	{
	case ESpotUpgrade::Tier0:
	{
		CurTier = ESpotUpgrade::Tier1;
		Renderer->SetSprite("wall_1.png");
		RequiredCoin = 3;
		break;
	}
	case ESpotUpgrade::Tier1:
	{
		CurTier = ESpotUpgrade::Tier2;
		Renderer->SetSprite("wall_2.png");
		RequiredCoin = 6;
		break;
	}
	case ESpotUpgrade::Tier2:
	{
		CurTier = ESpotUpgrade::Tier3;
		Renderer->SetSprite("wall_3.png");
		RequiredCoin = 0;
		IsUpgradable = false;
		break;
	}
	default:
		break;
	}

	Super::Upgrade();
}
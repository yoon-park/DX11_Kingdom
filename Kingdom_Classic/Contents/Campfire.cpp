#include "PreCompile.h"
#include "Campfire.h"

ACampfire::ACampfire()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);

	SetRoot(Root);
}

ACampfire::~ACampfire()
{

}

void ACampfire::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Campfire_00.png");
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderOrder::GroundObject);
}

void ACampfire::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ACampfire::Upgrade()
{
	switch (CurTier)
	{
	case ESpotUpgrade::Tier0:
	{
		CurTier = ESpotUpgrade::Tier1;
		Renderer->SetSprite("Campfire_01.png");
		break;
	}
	case ESpotUpgrade::Tier1:
	{
		CurTier = ESpotUpgrade::Tier2;
		Renderer->SetSprite("Campfire_02.png");
		break;
	}
	case ESpotUpgrade::Tier2:
	{
		CurTier = ESpotUpgrade::Tier3;
		Renderer->SetSprite("Campfire_03.png");
		break;
	}
	case ESpotUpgrade::Tier3:
	{
		CurTier = ESpotUpgrade::Tier4;
		break;
	}
	default:
		break;
	}
}
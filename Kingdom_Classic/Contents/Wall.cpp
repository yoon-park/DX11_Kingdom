#include "PreCompile.h"
#include "Wall.h"

AWall::AWall()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);

	SetRoot(Root);
}

AWall::~AWall()
{

}

void AWall::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("wall_1.png");
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
		break;
	}
	case ESpotUpgrade::Tier1:
	{
		CurTier = ESpotUpgrade::Tier2;
		break;
	}
	case ESpotUpgrade::Tier2:
	{
		CurTier = ESpotUpgrade::Tier3;
		break;
	}
	default:
		break;
	}
}
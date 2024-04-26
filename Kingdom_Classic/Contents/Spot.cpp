#include "PreCompile.h"
#include "Spot.h"

ASpot::ASpot()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	Renderer_Coin00 = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer_Coin00->SetupAttachment(Root);
	Renderer_Coin00->SetActive(false);

	/* Coins */

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

void ASpot::BeginPlay()
{
	Super::BeginPlay();

	{
		Renderer_Coin00->SetSprite("Coin_Indicator.png");
		Renderer_Coin00->SetAutoSize(1.0f, true);
		Renderer_Coin00->SetOrder(ERenderOrder::UI);

		/* Coins */
	}
}

void ASpot::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	CheckPlayer();
}

void ASpot::CheckPlayer()
{
	Collision_Update->CollisionStay(ECollisionOrder::Horse, [=](std::shared_ptr<UCollision> _Collision)
		{
			Renderer_Coin00->SetActive(true);
			return;
		}
	);

	Collision_Update->CollisionExit(ECollisionOrder::Horse, [=](std::shared_ptr<UCollision> _Collision)
		{
			Renderer_Coin00->SetActive(false);
			return;
		}
	);
}
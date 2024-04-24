#include "PreCompile.h"
#include "Spot.h"

ASpot::ASpot()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	CheckPlayerNearby = CreateDefaultSubObject<UCollision>("CheckPlayerNearby");
	CheckPlayerNearby->SetupAttachment(Root);
	CheckPlayerNearby->SetScale(FVector(800.0f, 800.0f, 100.0f));
	CheckPlayerNearby->SetCollisionGroup(ECollisionOrder::Spot);
	CheckPlayerNearby->SetCollisionType(ECollisionType::Rect);
}

ASpot::~ASpot()
{

}

void ASpot::BeginPlay()
{
	Super::BeginPlay();
}

void ASpot::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ASpot::Upgrade()
{

}
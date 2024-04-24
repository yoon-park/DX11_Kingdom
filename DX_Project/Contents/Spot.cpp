#include "PreCompile.h"
#include "Spot.h"

ASpot::ASpot()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
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
#include "PreCompile.h"
#include "KingdomActor.h"

AKingdomActor::AKingdomActor()
{

}

AKingdomActor::~AKingdomActor()
{

}

void AKingdomActor::BeginPlay()
{
	Super::BeginPlay();
}

void AKingdomActor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

bool AKingdomActor::IsGround()
{
	return false;
}
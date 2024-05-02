#include "PreCompile.h"
#include "Greedling.h"

AGreedling::AGreedling()
{
	Collision->SetScale(FVector(12.0f, 27.0f, 100.0f));
}

AGreedling::~AGreedling()
{

}

void AGreedling::BeginPlay()
{
	Super::BeginPlay();
}

void AGreedling::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AGreedling::CheckGround()
{

}
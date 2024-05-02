#include "PreCompile.h"
#include "Floater.h"

AFloater::AFloater()
{
	Collision->SetScale(FVector(12.0f, 27.0f, 100.0f));
}

AFloater::~AFloater()
{

}

void AFloater::BeginPlay()
{
	Super::BeginPlay();
}

void AFloater::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AFloater::CheckGround()
{

}
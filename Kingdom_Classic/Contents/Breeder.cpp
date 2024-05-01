#include "PreCompile.h"
#include "Breeder.h"

ABreeder::ABreeder()
{
	Collision->SetScale(FVector(12.0f, 27.0f, 100.0f));
	Collision->SetCollisionGroup(ECollisionOrder::Monster);
	Collision->SetCollisionType(ECollisionType::Rect);
}

ABreeder::~ABreeder()
{

}

void ABreeder::BeginPlay()
{
	Super::BeginPlay();
}

void ABreeder::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ABreeder::CheckGround()
{

}
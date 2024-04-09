#include "PreCompile.h"
#include "PlayGameMode.h"

#include "Player.h"
#include "PlayBack.h"

APlayGameMode::APlayGameMode()
{

}

APlayGameMode::~APlayGameMode()
{

}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));

	GetWorld()->SpawnActor<APlayer>("Player");

	std::shared_ptr<APlayBack> Back = GetWorld()->SpawnActor<APlayBack>("PlayBack");
	Back->SetActorLocation({ 0.0f, 0.0f, 500.0f });
}


void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
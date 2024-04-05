#include "PreCompile.h"
#include "Player.h"

APlayer::APlayer()
{
	Renderer = CreateDefaultSubObject<URenderer>("Renderer");

	Renderer->SetMesh("Rect");
	Renderer->SetMaterial("2DImage");
}

APlayer::~APlayer()
{

}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(100.0f, 100.0f, 100.0f));
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	float Speed = 100.0f;

	if (UEngineInput::IsPress('A') == true)
	{
		AddActorLocation(FVector::Left * _DeltaTime * Speed);
	}

	if (UEngineInput::IsPress('D') == true)
	{
		AddActorLocation(FVector::Right * _DeltaTime * Speed);
	}

	if (UEngineInput::IsPress('W') == true)
	{
		AddActorLocation(FVector::Up * _DeltaTime * Speed);
	}

	if (UEngineInput::IsPress('S') == true)
	{
		AddActorLocation(FVector::Down * _DeltaTime * Speed);
	}
}
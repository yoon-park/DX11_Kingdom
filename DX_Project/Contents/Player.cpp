#include "PreCompile.h"
#include "Player.h"

APlayer::APlayer()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	
	InputOn();
}

APlayer::~APlayer()
{

}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(300.0f, 300.0f, 100.0f));
	Renderer->SetSprite("KingdomTitle.png");
	Renderer->SetAutoSize(10.0f, true);
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	float Speed = 100.0f;

	if (IsPress('A') == true)
	{
		AddActorLocation(FVector::Left * _DeltaTime * Speed);
	}

	if (IsPress('D') == true)
	{
		AddActorLocation(FVector::Right * _DeltaTime * Speed);
	}

	if (IsPress('W') == true)
	{
		AddActorLocation(FVector::Up * _DeltaTime * Speed);
	}

	if (IsPress('S') == true)
	{
		AddActorLocation(FVector::Down * _DeltaTime * Speed);
	}

	if (IsPress(VK_NUMPAD1) == true)
	{
		Color.X += _DeltaTime;
	}

	if (IsPress(VK_NUMPAD2) == true)
	{
		Color.X -= _DeltaTime;
	}

	if (IsPress(VK_NUMPAD4) == true)
	{
		Color.Y += _DeltaTime;
	}

	if (IsPress(VK_NUMPAD5) == true)
	{
		Color.Y -= _DeltaTime;
	}

	if (IsPress(VK_NUMPAD7) == true)
	{
		Color.Z += _DeltaTime;
	}

	if (IsPress(VK_NUMPAD8) == true)
	{
		Color.Z -= _DeltaTime;
	}
}
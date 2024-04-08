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

	SetActorScale3D(FVector(300.0f, 300.0f, 100.0f));
	Renderer->Resources->SettingTexture("Image", "deer_walk_0.png", "POINT");
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

	if (UEngineInput::IsPress(VK_NUMPAD1) == true)
	{
		Color.X += _DeltaTime;
	}

	if (UEngineInput::IsPress(VK_NUMPAD2) == true)
	{
		Color.X -= _DeltaTime;
	}

	if (UEngineInput::IsPress(VK_NUMPAD4) == true)
	{
		Color.Y += _DeltaTime;
	}

	if (UEngineInput::IsPress(VK_NUMPAD5) == true)
	{
		Color.Y -= _DeltaTime;
	}

	if (UEngineInput::IsPress(VK_NUMPAD7) == true)
	{
		Color.Z += _DeltaTime;
	}

	if (UEngineInput::IsPress(VK_NUMPAD8) == true)
	{
		Color.Z -= _DeltaTime;
	}
}
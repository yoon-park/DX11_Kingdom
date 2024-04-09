#include "PreCompile.h"
#include "TitleLogo.h"

ATitleLogo::ATitleLogo()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
}

ATitleLogo::~ATitleLogo()
{

}

void ATitleLogo::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(300.0f, 300.0f, 100.0f));

	Renderer->CreateAnimation("Test", "Walk", 1.0f);
	Renderer->ChangeAnimation("Test");
}

void ATitleLogo::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
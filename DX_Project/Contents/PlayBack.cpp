#include "PreCompile.h"
#include "PlayBack.h"

APlayBack::APlayBack()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	
	InputOn();
}

APlayBack::~APlayBack()
{

}

void APlayBack::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(1280.0f, 720.0f, 100.0f));

	Renderer->SetSprite("Back.png");
}

void APlayBack::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
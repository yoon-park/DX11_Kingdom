#include "PreCompile.h"
#include "Campfire.h"

ACampfire::ACampfire()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");

	SetRoot(Renderer);
	InputOn();
}

ACampfire::~ACampfire()
{

}

void ACampfire::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Campfire_02.png");
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderOrder::GroundObject);
}

void ACampfire::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
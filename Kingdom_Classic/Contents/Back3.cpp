#include "PreCompile.h"
#include "Back3.h"

ABack3::ABack3()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");

	SetRoot(Renderer);
	InputOn();
}

ABack3::~ABack3()
{

}

void ABack3::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Map_03.png");
	Renderer->SetAutoSize(3.5f, true);
	Renderer->SetOrder(ERenderOrder::Back3);
}

void ABack3::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
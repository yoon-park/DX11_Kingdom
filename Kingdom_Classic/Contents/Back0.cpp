#include "PreCompile.h"
#include "Back0.h"

ABack0::ABack0()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");

	SetRoot(Renderer);
}

ABack0::~ABack0()
{

}

void ABack0::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Map_00.png");
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderOrder::Back0);
}

void ABack0::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
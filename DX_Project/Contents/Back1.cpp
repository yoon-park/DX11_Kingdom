#include "PreCompile.h"
#include "Back1.h"

ABack1::ABack1()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");

	SetRoot(Renderer);
	InputOn();
}

ABack1::~ABack1()
{

}

void ABack1::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("trees_curtain_01.png");
	Renderer->SetAutoSize(3.0f, true);
	Renderer->SetOrder(ERenderOrder::Back1);
}

void ABack1::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
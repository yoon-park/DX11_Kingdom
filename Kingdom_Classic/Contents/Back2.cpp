#include "PreCompile.h"
#include "Back2.h"

ABack2::ABack2()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");

	SetRoot(Renderer);
}

ABack2::~ABack2()
{

}

void ABack2::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Map_02.png");
	Renderer->SetAutoSize(3.0f, true);
	Renderer->SetOrder(ERenderOrder::Back2);
}

void ABack2::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
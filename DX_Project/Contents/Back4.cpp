#include "PreCompile.h"
#include "Back4.h"

ABack4::ABack4()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");

	SetRoot(Renderer);
	InputOn();
}

ABack4::~ABack4()
{

}

void ABack4::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("backdrop_rocks.png");
	Renderer->SetAutoSize(3.5f, true);
	Renderer->SetOrder(ERenderOrder::Back4);
}

void ABack4::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
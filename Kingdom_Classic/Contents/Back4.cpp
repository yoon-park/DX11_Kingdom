#include "PreCompile.h"
#include "Back4.h"

ABack4::ABack4()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");

	SetRoot(Renderer);
}

ABack4::~ABack4()
{

}

void ABack4::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Map_04.png");
	Renderer->SetAutoSize(5.0f, true);
	Renderer->SetOrder(ERenderOrder::Back4);
}

void ABack4::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
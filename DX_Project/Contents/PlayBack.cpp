#include "PreCompile.h"
#include "PlayBack.h"

APlayBack::APlayBack()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");

	SetRoot(Renderer);
	
	InputOn();
}

APlayBack::~APlayBack()
{

}

void APlayBack::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Back.png");
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderOrder::Back);
}

void APlayBack::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
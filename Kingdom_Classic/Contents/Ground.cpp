#include "PreCompile.h"
#include "Ground.h"

AGround::AGround()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");

	SetRoot(Renderer);
	InputOn();
}

AGround::~AGround()
{

}

void AGround::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Ground.png");
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderOrder::Ground);
}

void AGround::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
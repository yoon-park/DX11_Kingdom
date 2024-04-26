#include "PreCompile.h"
#include "Ground_Back.h"

AGround_Back::AGround_Back()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");

	SetRoot(Renderer);
}

AGround_Back::~AGround_Back()
{

}

void AGround_Back::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Back.png");
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderOrder::Ground);
}

void AGround_Back::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
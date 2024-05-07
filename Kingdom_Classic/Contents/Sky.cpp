#include "PreCompile.h"
#include "Sky.h"

ASky::ASky()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");

	SetRoot(Renderer);
}

ASky::~ASky()
{

}

void ASky::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("KingdomTitle.png");
	Renderer->SetAutoSize(3.0f, true);
	Renderer->SetOrder(ERenderOrder::Sky);
	Renderer->SetPlusColor({0.0f, 0.0f, 1.0f, 0.5f});
}

void ASky::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
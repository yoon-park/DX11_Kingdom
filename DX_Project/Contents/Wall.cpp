#include "PreCompile.h"
#include "Wall.h"

AWall::AWall()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");

	SetRoot(Renderer);
}

AWall::~AWall()
{

}

void AWall::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("TownCenter_02.png");
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderOrder::GroundObject);
}

void AWall::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
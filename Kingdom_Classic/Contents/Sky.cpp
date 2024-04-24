#include "PreCompile.h"
#include "Sky.h"

ASky::ASky()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");

	SetRoot(Renderer);
	InputOn();
}

ASky::~ASky()
{

}

void ASky::BeginPlay()
{
	Super::BeginPlay();
}

void ASky::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
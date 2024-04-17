#include "PreCompile.h"
#include "PlayBackBack.h"

APlayBackBack::APlayBackBack()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");

	SetRoot(Renderer);

	InputOn();
}

APlayBackBack::~APlayBackBack()
{

}

void APlayBackBack::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("rocks_big_05.png");
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderOrder::Back);
}

void APlayBackBack::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
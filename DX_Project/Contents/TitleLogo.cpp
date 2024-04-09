#include "PreCompile.h"
#include "TitleLogo.h"

ATitleLogo::ATitleLogo()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
}

ATitleLogo::~ATitleLogo()
{

}

void ATitleLogo::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(700.0f, 300.0f, 100.0f));

	DelayCallback(1.0f, std::bind(&ATitleLogo::RendererOff, this));
	Renderer->SetSprite("CuttingTest.png", 11);
	Renderer->CreateAnimation("Test", "CuttingTest.png", 0.1f);
	Renderer->ChangeAnimation("Test");
}

void ATitleLogo::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ATitleLogo::RendererOn()
{
	Renderer->SetSprite("CuttingTest.png", 11);
	DelayCallback(1.0f, std::bind(&ATitleLogo::RendererOff, this));
}

void ATitleLogo::RendererOff()
{
	Renderer->SetSprite("CuttingTest.png", 11);
	DelayCallback(1.0f, std::bind(&ATitleLogo::RendererOn, this));
}
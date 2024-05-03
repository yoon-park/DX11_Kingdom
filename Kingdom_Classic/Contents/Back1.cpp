#include "PreCompile.h"
#include "Back1.h"

ABack1::ABack1()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);

	Renderer_Lightbeam = CreateDefaultSubObject<USpriteRenderer>("Renderer_Lightbeam");
	Renderer_Lightbeam->SetupAttachment(Root);

	SetRoot(Root);
}

ABack1::~ABack1()
{

}

void ABack1::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Map_01.png");
	Renderer->SetAutoSize(1.5f, true);
	Renderer->SetOrder(ERenderOrder::Back1);

	Renderer_Lightbeam->SetSprite("Lightbeam_01.png");
	Renderer_Lightbeam->SetAutoSize(1.5f, true);
	Renderer_Lightbeam->SetPosition({ 2150.0f, -15.0f, 0.0f });
	Renderer_Lightbeam->SetMulColor(float4(1.0f, 1.0f, 1.0f, 0.5f));
	Renderer_Lightbeam->SetOrder(ERenderOrder::Back0);
}

void ABack1::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
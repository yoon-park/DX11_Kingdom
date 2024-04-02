#include "PreCompile.h"
#include "Renderer.h"

URenderer::URenderer()
{

}

URenderer::~URenderer()
{

}

void URenderer::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->PushRenderer(shared_from_this());
}

void URenderer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void URenderer::Render(float _DeltaTime)
{

}
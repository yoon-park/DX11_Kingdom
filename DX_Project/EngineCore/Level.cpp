#include "PreCompile.h"
#include "Level.h"

#include "GameMode.h"
#include "Renderer.h"
#include "Camera.h"

bool ULevel::IsActorConstructor = true;

ULevel::ULevel()
{
	MainCamera = std::make_shared<UCamera>();
}

ULevel::~ULevel()
{

}

void ULevel::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	for (std::pair<const int, std::list<std::shared_ptr<AActor>>>& TickGroup : Actors)
	{
		std::list<std::shared_ptr<AActor>>& GroupActors = TickGroup.second;

		for (std::shared_ptr<AActor> Actor : GroupActors)
		{
			Actor->Tick(_DeltaTime);
		}
	}
}

void ULevel::Render(float _DeltaTime)
{
	for (std::pair<const int, std::list<std::shared_ptr<URenderer>>>& RenderGroup : Renderers)
	{
		std::list<std::shared_ptr<URenderer>>& GroupRenderers = RenderGroup.second;

		for (std::shared_ptr<URenderer> Renderer : GroupRenderers)
		{
			Renderer->Render(_DeltaTime);
		}
	}
}

void ULevel::PushActor(std::shared_ptr<AActor> _Actor)
{
	if (_Actor == nullptr)
	{
		MsgBoxAssert("만들어지지 않은 액터를 레벨에 추가하려 했습니다.");
		return;
	}

	_Actor->SetWorld(this);
	_Actor->RootCheck();
	_Actor->BeginPlay();

	Actors[_Actor->GetOrder()].push_back(_Actor);
}

void ULevel::PushRenderer(std::shared_ptr<URenderer> _Renderer)
{
	Renderers[_Renderer->GetOrder()].push_front(_Renderer);
}
#include "PreCompile.h"
#include "Actor.h"

#include "SceneComponent.h"
#include "DefaultSceneComponent.h"

AActor::AActor()
{

}

AActor::~AActor()
{

}

FTransform& AActor::GetActorTransform()
{
	return RootComponent->Transform;
}

void AActor::BeginPlay()
{
	Super::BeginPlay();

	for (size_t i = 0; i < Components.size(); i++)
	{
		Components[i]->SetWorld(GetWorld());
		Components[i]->BeginPlay();
	}
}

void AActor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	for (size_t i = 0; i < Components.size(); i++)
	{
		Components[i]->Tick(_DeltaTime);
	}
}

void AActor::RootCheck()
{
	if (RootComponent == nullptr)
	{
		RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>("UDefaultSceneComponent");
	}
}

void AActor::PushComponent(std::shared_ptr<UActorComponent> _Component, std::string_view _Name)
{
	_Component->SetActor(this);
	_Component->SetName(_Name);
	Components.push_back(_Component);

	std::shared_ptr<USceneComponent> SceneComponent = std::dynamic_pointer_cast<USceneComponent>(_Component);

	if (RootComponent == nullptr && SceneComponent != nullptr)
	{
		RootComponent = SceneComponent.get();
	}
}
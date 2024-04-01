#pragma once
#include "TickObject.h"
#include "WorldObject.h"
#include "Level.h"

class ULevel;
class UActorComponent;
class USceneComponent;

class AActor : public UTickObject, public UWorldObject
{
	GENERATED_BODY(UTickObject)

	friend ULevel;

public:
	AActor();
	~AActor();

	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;

	template<typename ComponentType>
	std::shared_ptr<ComponentType> CreateDefaultSubobject(std::string_view _Name)
	{
		if (ULevel::IsActorConstructor == false)
		{
			MsgBoxAssert("생성자 밖에서는 컴포넌트를 생성할수 없습니다. (언리얼엔진 참고)");
		}

		std::shared_ptr<UActorComponent> NewComponent = std::make_shared<ComponentType>();

		PushComponent(NewComponent, _Name);

		return std::dynamic_pointer_cast<ComponentType>(NewComponent);
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USceneComponent* RootComponent = nullptr;
	std::vector<std::shared_ptr<UActorComponent>> Components;

	void PushComponent(std::shared_ptr<UActorComponent> _Component, std::string_view _Name);
};
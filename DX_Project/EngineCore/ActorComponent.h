#pragma once
#include "TickObject.h"
#include "WorldObject.h"
#include "Actor.h"

class UActorComponent : public UTickObject, public UNameObject, public UWorldObject
{
	friend AActor;

public:
	UActorComponent();
	~UActorComponent();

	UActorComponent(const UActorComponent& _Other) = delete;
	UActorComponent(UActorComponent&& _Other) noexcept = delete;
	UActorComponent& operator=(const UActorComponent& _Other) = delete;
	UActorComponent& operator=(UActorComponent&& _Other) noexcept = delete;

protected:

private:
	AActor* Actor = nullptr;

	void SetActor(AActor* _Actor)
	{
		Actor = _Actor;
	}
};
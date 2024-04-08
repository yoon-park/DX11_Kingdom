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

	bool IsActive()
	{
		return ActiveValue;
	}

	void SetActive(bool _Value)
	{
		ActiveValue = _Value;
	}

protected:

private:
	AActor* Actor = nullptr;
	bool ActiveValue = true;

	void SetActor(AActor* _Actor)
	{
		Actor = _Actor;
	}
};
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

	AActor* GetActor()
	{
		return Actor;
	}

	void SetActive(bool _Value)
	{
		ActiveValue = _Value;
	}

	bool IsActive()
	{
		return ActiveValue;
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
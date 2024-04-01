#pragma once
#include "ActorComponent.h"

class USceneComponent : public UActorComponent, public UTransformObject
{
public:
	USceneComponent();
	~USceneComponent();

	USceneComponent(const USceneComponent& _Other) = delete;
	USceneComponent(USceneComponent&& _Other) noexcept = delete;
	USceneComponent& operator=(const USceneComponent& _Other) = delete;
	USceneComponent& operator=(USceneComponent&& _Other) noexcept = delete;

protected:

private:

};
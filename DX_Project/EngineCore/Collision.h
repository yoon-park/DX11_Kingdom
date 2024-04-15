#pragma once
#include "SceneComponent.h"

class UCollision : public USceneComponent
{
public:
	UCollision();
	~UCollision();

	UCollision(const UCollision& _Other) = delete;
	UCollision(UCollision&& _Other) noexcept = delete;
	UCollision& operator=(const UCollision& _Other) = delete;
	UCollision& operator=(UCollision&& _Other) noexcept = delete;

protected:

private:

};
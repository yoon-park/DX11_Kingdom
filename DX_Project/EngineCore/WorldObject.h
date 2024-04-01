#pragma once
#include "Level.h"

class AActor;
class ULevel;

class UWorldObject
{
public:
	friend AActor;
	friend ULevel;

	UWorldObject();
	~UWorldObject();

	UWorldObject(const UWorldObject& _Other) = delete;
	UWorldObject(UWorldObject&& _Other) noexcept = delete;
	UWorldObject& operator=(const UWorldObject& _Other) = delete;
	UWorldObject& operator=(UWorldObject&& _Other) noexcept = delete;

	ULevel* GetWorld()
	{
		return World;
	}

protected:

private:
	ULevel* World = nullptr;

	void SetWorld(ULevel* _World)
	{
		World = _World;
	}
};
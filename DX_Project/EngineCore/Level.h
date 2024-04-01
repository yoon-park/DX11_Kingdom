#pragma once
#include "TickObject.h"

class AActor;
class AGameMode;
class UEngineCore;

class ULevel final : public UTickObject, public UNameObject
{
	GENERATED_BODY(UTickObject)

	friend AActor;
	friend UEngineCore;

public:
	ULevel();
	~ULevel();

	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	static bool IsActorConstructor;

	template<typename ActorType>
	void SpawnActor(std::string _Name, int _Order = 0)
	{
		IsActorConstructor = true;
		std::shared_ptr<AActor> NewActor = std::make_shared<ActorType>();
		IsActorConstructor = false;
		
		PushActor(NewActor);
	}

protected:
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<AGameMode> GameMode;
	std::map<int, std::list<std::shared_ptr<AActor>>> Actors;

	void PushActor(std::shared_ptr<AActor> _Actor);
	void ActorInit(std::shared_ptr<AActor> _Actor);
};
#pragma once
#include "TickObject.h"

class AActor;
class AGameMode;
class URenderer;
class UCamera;
class UEngineCore;

class ULevel final : public UTickObject, public UNameObject
{
	GENERATED_BODY(UTickObject)

	friend AActor;
	friend URenderer;
	friend UEngineCore;

public:
	ULevel();
	~ULevel();

	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	static bool IsActorConstructor;

	std::shared_ptr<UCamera> GetMainCamera()
	{
		return MainCamera;
	}

	template<typename ActorType>
	std::shared_ptr<ActorType> SpawnActor(std::string _Name, int _Order = 0)
	{
		IsActorConstructor = true;
		std::shared_ptr<AActor> NewActor = std::make_shared<ActorType>();
		ConstructorActor(NewActor);
		IsActorConstructor = false;
		PushActor(NewActor);

		return std::dynamic_pointer_cast<ActorType>(NewActor);
	}

protected:
	void Tick(float _DeltaTime) override;
	void Render(float _DeltaTime);

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

private:
	std::shared_ptr<AGameMode> GameMode;
	std::map<int, std::list<std::shared_ptr<AActor>>> Actors;
	std::map<int, std::list<std::shared_ptr<URenderer>>> Renderers;

	std::shared_ptr<UCamera> MainCamera = nullptr;
	std::shared_ptr<UCamera> UICamera = nullptr;

	void ConstructorActor(std::shared_ptr<AActor> _Actor);
	void PushActor(std::shared_ptr<AActor> _Actor);
	void PushRenderer(std::shared_ptr<URenderer> _Renderer);
};
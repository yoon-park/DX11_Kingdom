#pragma once
#include "TickObject.h"

class UEngineCore;
class URenderer;
class UCamera;
class UCollision;
class AActor;
class AGameMode;

class ULevel final : public UTickObject, public UNameObject
{
	GENERATED_BODY(UTickObject)

	friend UEngineCore;
	friend URenderer;
	friend UCollision;
	friend AActor;

public:
	ULevel();
	~ULevel();

	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	static bool IsActorConstructer;

	std::shared_ptr<UCamera> GetMainCamera()
	{
		return MainCamera;
	}

	template<typename EnumType>
	std::list<std::shared_ptr<AActor>> GetTickGroup(EnumType _Type)
	{
		return GetTickGroup(static_cast<int>(_Type));
	}

	std::list<std::shared_ptr<AActor>> GetTickGroup(int _Order)
	{
		return Actors[_Order];
	}

	template<typename ActorType, typename EnumType>
	std::shared_ptr<ActorType> SpawnActor(std::string_view _Name, EnumType _Order)
	{
		return SpawnActor<ActorType>(_Name, static_cast<int>(_Order));
	}

	template<typename ActorType>
	std::shared_ptr<ActorType> SpawnActor(std::string_view _Name, int _Order = 0)
	{
		IsActorConstructer = true;
		std::shared_ptr<AActor> NewActor = std::make_shared<ActorType>();
		ConstructorActor(NewActor, _Name, _Order);
		IsActorConstructer = false;

		PushActor(NewActor);
		return std::dynamic_pointer_cast<ActorType>(NewActor);
	}

protected:
	void Tick(float _DeltaTime) override;
	void Render(float _DeltaTime);

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

	void Destroy();

private:
	std::shared_ptr<UCamera> MainCamera = nullptr;
	std::shared_ptr<UCamera> UICamera = nullptr;
	std::shared_ptr<AGameMode> GameMode;

	std::map<int, std::list<std::shared_ptr<AActor>>> Actors;
	std::map<int, std::list<std::shared_ptr<URenderer>>> Renderers;
	std::map<int, std::list<std::shared_ptr<UCollision>>> Collisions;

	void ConstructorActor(std::shared_ptr<AActor> _Actor, std::string_view _Name, int Order);
	void PushActor(std::shared_ptr<AActor> _Actor);
	void PushRenderer(std::shared_ptr<URenderer> _Renderer);
	void PushCollision(std::shared_ptr<UCollision> _Collision);
	void ChangeOrderRenderer(std::shared_ptr<URenderer> _Renderer, int _PrevOrder, int _ChangeOrder);
	void ChangeOrderCollision(std::shared_ptr<UCollision> _Collision, int _PrevOrder, int _ChangeOrder);
};
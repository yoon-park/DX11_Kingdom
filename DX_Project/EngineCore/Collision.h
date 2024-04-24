#pragma once
#include "SceneComponent.h"

class UCollision : public USceneComponent, public std::enable_shared_from_this<UCollision>
{
	GENERATED_BODY(USceneComponent)

public:
	UCollision();
	~UCollision();

	UCollision(const UCollision& _Other) = delete;
	UCollision(UCollision&& _Other) noexcept = delete;
	UCollision& operator=(const UCollision& _Other) = delete;
	UCollision& operator=(UCollision&& _Other) noexcept = delete;

	void SetCollisionType(ECollisionType _CollisionType)
	{
		CollisionType = _CollisionType;
	}

	template<typename EnumType>
	void SetCollisionGroup(EnumType _Index)
	{
		SetCollisionGroup(static_cast<int>(_Index));
	}

	void SetCollisionGroup(int _Index);

	template<typename EnumType>
	void SetOrder(EnumType _Order)
	{
		SetOrder(static_cast<int>(_Order));
	}

	void SetOrder(int _Order) override;

	template<typename EnumType>
	bool CollisionEnter(EnumType _TargetGroup, std::function<void(std::shared_ptr<UCollision>)> _Function = nullptr)
	{
		return CollisionEnter(static_cast<int>(_TargetGroup), _Function);
	}

	bool CollisionEnter(int _TargetGroup, std::function<void(std::shared_ptr<UCollision>)> _Function = nullptr);

	template<typename EnumType>
	bool CollisionStay(EnumType _TargetGroup, std::function<void(std::shared_ptr<UCollision>)> _Function = nullptr)
	{
		return CollisionStay(static_cast<int>(_TargetGroup), _Function);
	}

	bool CollisionStay(int _TargetGroup, std::function<void(std::shared_ptr<UCollision>)> _Function = nullptr);

	template<typename EnumType>
	bool CollisionExit(EnumType _TargetGroup, std::function<void(std::shared_ptr<UCollision>)> _Function = nullptr)
	{
		return CollisionExit(static_cast<int>(_TargetGroup), _Function);
	}

	bool CollisionExit(int _TargetGroup, std::function<void(std::shared_ptr<UCollision>)> _Function = nullptr);

	bool Collision(int _TargetGroup,
		std::function<void(std::shared_ptr<UCollision>)> _Enter = nullptr,
		std::function<void(std::shared_ptr<UCollision>)> _Stay = nullptr,
		std::function<void(std::shared_ptr<UCollision>)> _Exit = nullptr);

protected:
	void BeginPlay() override;

private:
	ECollisionType CollisionType = ECollisionType::CirCle;

	std::set<UCollision*> OtherCheck;
};


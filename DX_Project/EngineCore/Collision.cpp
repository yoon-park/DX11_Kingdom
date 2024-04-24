#include "PreCompile.h"
#include "Collision.h"

UCollision::UCollision() 
{

}

UCollision::~UCollision() 
{

}

void UCollision::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->PushCollision(shared_from_this());
}

void UCollision::SetCollisionGroup(int _Index)
{
	SetOrder(_Index);
}

void UCollision::SetOrder(int _Order)
{
	int PrevOrder = GetOrder();

	Super::SetOrder(_Order);

	if (GetWorld() != nullptr)
	{
		GetWorld()->ChangeOrderCollision(shared_from_this(), PrevOrder, _Order);
	}
}

bool UCollision::CollisionEnter(int _TargetGroup, std::function<void(std::shared_ptr<UCollision>)> _Function /*= nullptr*/)
{
	return Collision(_TargetGroup, _Function, nullptr, nullptr);
}

bool UCollision::CollisionStay(int _TargetGroup, std::function<void(std::shared_ptr<UCollision>)> _Function /*= nullptr*/)
{
	return Collision(_TargetGroup, nullptr, _Function, nullptr);
}

bool UCollision::CollisionExit(int _TargetGroup, std::function<void(std::shared_ptr<UCollision>)> _Function /*= nullptr*/)
{
	return Collision(_TargetGroup, nullptr, nullptr, _Function);
}

bool UCollision::Collision(int _TargetGroup,
	std::function<void(std::shared_ptr<UCollision>)> _Enter /*= nullptr*/,
	std::function<void(std::shared_ptr<UCollision>)> _Stay /*= nullptr*/,
	std::function<void(std::shared_ptr<UCollision>)> _Exit /*= nullptr*/)
{
	auto Test = GetWorld()->Collisions;

	std::list<std::shared_ptr<UCollision>>& Group = GetWorld()->Collisions[_TargetGroup];

	if (IsActive() == false)
	{
		return false;
	}

	for (std::shared_ptr<UCollision> OtherCollision : Group)
	{
		ECollisionType ThisType = CollisionType;
		ECollisionType OtherType = OtherCollision->CollisionType;

		UCollision* CollisionPtr = OtherCollision.get();

		if (Transform.Collision(ThisType, OtherType, OtherCollision->Transform) == true)
		{
			bool IsFirst = false;

			if (OtherCheck.contains(CollisionPtr) == false)
			{
				IsFirst = true;
			}
			else 
			{
				IsFirst = false;
			}

			if (_Enter != nullptr || _Exit != nullptr)
			{
				OtherCheck.insert(CollisionPtr);
			}

			if (IsFirst == true && _Enter != nullptr)
			{
				_Enter(OtherCollision);
			}
			else if (IsFirst == false && _Stay != nullptr)
			{
				_Stay(OtherCollision);
			}
		}
		else if(OtherCheck.contains(CollisionPtr) == true && _Exit != nullptr)
		{
			OtherCheck.erase(CollisionPtr);
			_Exit(OtherCollision);
		}
	}

	return false;
}
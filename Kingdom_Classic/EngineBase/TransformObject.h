#pragma once
#include "Transform.h"

class UTransformObject
{
public:
	UTransformObject();
	~UTransformObject();

	UTransformObject(const UTransformObject& _Other) = delete;
	UTransformObject(UTransformObject&& _Other) noexcept = delete;
	UTransformObject& operator=(const UTransformObject& _Other) = delete;
	UTransformObject& operator=(UTransformObject&& _Other) noexcept = delete;

	FTransform Transform;

	FVector GetWorldRight()
	{
		return Transform.World.ArrVector[0].Normalize3DReturn();
	}

	FVector GetWorldLeft()
	{
		return -GetWorldRight();
	}

	FVector GetWorldUp()
	{
		return Transform.World.ArrVector[1].Normalize3DReturn();
	}

	FVector GetWorldDown()
	{
		return -GetWorldUp();
	}

	FVector GetWorldForward()
	{
		return Transform.World.ArrVector[2].Normalize3DReturn();
	}

	FVector GetWorldBack()
	{
		return -GetWorldForward();
	}

	FVector GetLocalScale() const
	{
		return Transform.LocalScale;
	}

	FVector GetLocalRotation() const
	{
		return Transform.LocalRotation;
	}

	FVector GetLocalPosition() const
	{
		return Transform.LocalPosition;
	}

	FVector GetWorldScale() const
	{
		return Transform.WorldScale;
	}

	FVector GetWorldRotation() const
	{
		return Transform.WorldRotation;
	}

	FVector GetWorldPosition() const
	{
		return Transform.WorldPosition;
	}

	void SetParent(UTransformObject* _Parent)
	{
		Parent = _Parent;
		Parent->Transform.TransformUpdate();
		Parent->Childs.push_back(this);
		ChildUpdate();
	}

	void SetScale(FVector _Value)
	{
		Transform.SetScale(_Value);
		ChildUpdate();
	}

	void SetRotationDeg(FVector _Value)
	{
		Transform.SetRotationDeg(_Value);
		ChildUpdate();
	}

	void SetPosition(FVector _Value)
	{
		Transform.SetPosition(_Value);
		ChildUpdate();
	}

	void AddScale(FVector _Value)
	{
		Transform.AddScale(_Value);
		ChildUpdate();
	}

	void AddRotationDeg(FVector _Value)
	{
		Transform.AddRotationDeg(_Value);
		ChildUpdate();
	}

	void AddPosition(FVector _Value)
	{
		Transform.AddPosition(_Value);
		ChildUpdate();
	}

	void ChildUpdate();

protected:

private:
	UTransformObject* Parent = nullptr;
	std::vector<UTransformObject*> Childs;
};
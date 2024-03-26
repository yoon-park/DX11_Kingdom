#pragma once
#include "EngineMath.h"

enum class ECollisionType
{
	Point,
	CirCle,
	Rect,
	Max,
};

class CollisionFunctionInit;

class FTransform
{
	friend CollisionFunctionInit;

private:
	static bool (*CollisionFunction[static_cast<int>(ECollisionType::Max)][static_cast<int>(ECollisionType::Max)])(const FTransform& _Left, const FTransform& _Right);

public:
	FTransform();
	FTransform(const FVector& _Pos, const FVector& _Scale)
		: Position(_Pos), Scale(_Scale)
	{

	}
	~FTransform();

	/*
	FTransform(const FTransform& _Other) = delete;
	FTransform(FTransform&& _Other) noexcept = delete;
	FTransform& operator=(const FTransform& _Other) = delete;
	FTransform& operator=(FTransform&& _Other) noexcept = delete;
	*/

	static bool CircleToCircle(const FTransform& _Left, const FTransform& _Right);
	static bool CircleToRect(const FTransform& _Left, const FTransform& _Right);
	static bool CircleToPoint(const FTransform& _Left, const FTransform& _Right);

	static bool RectToRect(const FTransform& _Left, const FTransform& _Right);
	static bool RectToCircle(const FTransform& _Left, const FTransform& _Right);
	static bool RectToPoint(const FTransform& _Left, const FTransform& _Right);

	static bool PointToRect(const FTransform& _Left, const FTransform& _Right);
	static bool PointToCircle(const FTransform& _Left, const FTransform& _Right);

	FVector GetScale() const
	{
		return Scale;
	}

	FVector GetRotation() const
	{
		return Rotation;
	}

	FVector GetPosition() const
	{
		return Position;
	}

	float GetRadius() const
	{
		return Scale.hX();
	}

	void SetScale(FVector _Value)
	{
		Scale = _Value;
	}

	void SetRotation(FVector _Value)
	{
		Rotation = _Value;
	}

	void SetPosition(FVector _Value)
	{
		Position = _Value;
	}

	void SetRadius(float _Radius)
	{
		Scale = float4::Zero;
		Scale.X = _Radius * 2.0f;
	}

	void AddScale(FVector _Value)
	{
		Scale += _Value;
	}

	void AddRotation(FVector _Value)
	{
		Rotation += _Value;
	}

	void AddPosition(FVector _Value)
	{
		Position += _Value;
	}

	FVector LeftTop() const
	{
		return { Left(), Top() };
	}

	FVector LeftBottom() const
	{
		return { Left(), Bottom() };
	}

	FVector RightTop() const
	{
		return { Right(), Top() };
	}

	FVector RightBottom() const
	{
		return { Right(), Bottom() };
	}

	float Left() const
	{
		return Position.X - Scale.hX();
	}

	float Right() const
	{
		return Position.X + Scale.hX();
	}

	float Top() const
	{
		return Position.Y - Scale.hY();
	}

	float Bottom() const
	{
		return Position.Y + Scale.hY();
	}

	int iLeft() const
	{
		return std::lround(Left());
	}

	int iRight() const
	{
		return std::lround(Right());
	}

	int iTop() const
	{
		return std::lround(Top());
	}

	int iBottom() const
	{
		return std::lround(Bottom());
	}

	bool Collision(ECollisionType _ThisType, ECollisionType _OtherType, const FTransform& _Other);

protected:

private:
	FVector Scale = FVector::One;
	FVector Rotation = FVector::Zero;
	FVector Position = FVector::Zero;
};


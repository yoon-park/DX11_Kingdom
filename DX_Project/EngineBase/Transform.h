#pragma once
#include "EngineMath.h"

enum class ECollisionType
{
	Point,
	CirCle,
	Rect,
	RotRect,
	Sphere,
	Box,
	RotBox,
	Max,
};

class CollisionData
{
public:
	union 
	{
		// 구
		DirectX::BoundingSphere Sphere;
		// 회전하지 않은 사각형
		DirectX::BoundingBox AABB;
		// 회전한 사각형
		DirectX::BoundingOrientedBox OBB;
	};

	CollisionData()
		: OBB(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f))
	{

	}
};

class CollisionFunctionInit;

struct FTransform
{
	friend CollisionFunctionInit;

private:
	static bool (*CollisionFunction[static_cast<int>(ECollisionType::Max)][static_cast<int>(ECollisionType::Max)])(const FTransform& _Left, const FTransform& _Right);

public:
	FTransform();
	FTransform(const FVector& _Pos, const FVector& _Scale)
		: LocalPosition(_Pos), LocalScale(_Scale)
	{

	}
	~FTransform();

	//FTransform(const FTransform& _Other) = delete;
	//FTransform(FTransform&& _Other) noexcept = delete;
	//FTransform& operator=(const FTransform& _Other) = delete;
	//FTransform& operator=(FTransform&& _Other) noexcept = delete;

	static bool CircleToCircle(const FTransform& _Left, const FTransform& _Right);
	static bool CircleToRect(const FTransform& _Left, const FTransform& _Right);
	static bool CircleToRotRect(const FTransform& _Left, const FTransform& _Right);
	static bool CircleToPoint(const FTransform& _Left, const FTransform& _Right);

	static bool RectToCircle(const FTransform& _Left, const FTransform& _Right);
	static bool RectToRect(const FTransform& _Left, const FTransform& _Right);
	static bool RectToPoint(const FTransform& _Left, const FTransform& _Right);

	static bool RotRectToRotRect(const FTransform& _Left, const FTransform& _Right);

	static bool PointToCircle(const FTransform& _Left, const FTransform& _Right);
	static bool PointToRect(const FTransform& _Left, const FTransform& _Right);

	float4 LocalScale;
	float4 LocalRotation;
	float4 LocalPosition;
	float4 WorldScale;
	float4 WorldRotation;
	float4 WorldPosition;
	float4x4 ScaleMat;
	float4x4 RotationMat;
	float4x4 PositionMat;
	float4x4 ParentMat;
	float4x4 LocalWorld;
	float4x4 World;
	float4x4 View;
	float4x4 Projection;
	float4x4 WVP;

	FVector GetRight()
	{
		return World.ArrVector[0].Normalize3DReturn();
	}

	FVector GetLeft()
	{
		return -GetRight();
	}

	FVector GetUp()
	{
		return World.ArrVector[1].Normalize3DReturn();
	}

	FVector GetDown()
	{
		return -GetUp();
	}

	FVector GetForward()
	{
		return World.ArrVector[2].Normalize3DReturn();
	}

	FVector GetBack()
	{
		return -GetForward();
	}

	FVector GetScale() const
	{
		return LocalScale;
	}

	FVector GetRotation() const
	{
		return LocalRotation;
	}

	FVector GetPosition() const
	{
		return LocalPosition;
	}

	float GetRadius() const
	{
		return LocalScale.hX();
	}

	CollisionData GetCollisionData() const
	{
		CollisionData Result;
		Result.OBB.Center = WorldPosition.DirectFloat3;
		Result.OBB.Extents = (WorldScale * 0.5f).DirectFloat3;
		Result.OBB.Orientation = WorldRotation.DegToQuaternion().DirectFloat4;
	}

	CollisionData GetCollisionData2D() const
	{
		CollisionData Result;
		Result.OBB.Center = WorldPosition.DirectFloat3;
		Result.OBB.Center.z = 0.0f;
		Result.OBB.Extents = (WorldScale* 0.5f).DirectFloat3;
		Result.OBB.Orientation = WorldRotation.DegToQuaternion().DirectFloat4;
		return Result;
	}

	void SetScale(FVector _Value)
	{
		LocalScale = _Value;
		TransformUpdate();
	}

	void SetRotationDeg(FVector _Value)
	{
		LocalRotation = _Value;
		TransformUpdate();
	}

	void SetPosition(FVector _Value)
	{
		LocalPosition = _Value;
		TransformUpdate();
	}

	void SetRadius(float _Radius)
	{
		LocalScale = float4::Zero;
		LocalScale.X = _Radius * 2.0f;
	}

	void AddScale(FVector _Value)
	{
		SetScale(LocalScale + _Value);
	}

	void AddRotationDeg(FVector _Value)
	{
		SetRotationDeg(LocalRotation + _Value);
	}

	void AddPosition(FVector _Value)
	{
		SetPosition(LocalPosition + _Value);
	}

	float Left() const
	{
		return LocalPosition.X - LocalScale.hX();
	}

	float Right() const
	{
		return LocalPosition.X + LocalScale.hX();
	}

	float Top() const
	{
		return LocalPosition.Y - LocalScale.hY();
	}

	float Bottom() const
	{
		return LocalPosition.Y + LocalScale.hY();
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

	FVector LeftTop() const
	{
		return { Left(), Top() };
	}

	FVector RightTop() const
	{
		return { Right(), Top() };
	}

	FVector LeftBottom() const
	{
		return { Left(), Bottom() };
	}

	FVector RightBottom() const
	{
		return { Right(), Bottom() };
	}

	void TransformUpdate();
	void CalculateViewAndProjection(FMatrix _View, FMatrix _Projection);
	bool Collision(ECollisionType _ThisType, ECollisionType _OtherType, const FTransform& _Other);

protected:

private:

};
#pragma once

class AMovingActor : public AActor
{
	GENERATED_BODY(AActor)

public:
	AMovingActor();
	~AMovingActor();

	AMovingActor(const AMovingActor& _Other) = delete;
	AMovingActor(AMovingActor&& _Other) noexcept = delete;
	AMovingActor& operator=(const AMovingActor& _Other) = delete;
	AMovingActor& operator=(AMovingActor&& _Other) noexcept = delete;

protected:
	EEngineDir PrevDir = EEngineDir::Right;
	EEngineDir CurDir = EEngineDir::Right;
	bool IsGround = false;
	EGroundType CurGroundType = EGroundType::None;

	float Speed = 0.0f;
	FVector MoveVector = FVector::Zero;
	float MoveAcc = 0.0f;
	FVector JumpVector = FVector::Zero;
	FVector GravityVector = FVector::Zero;
	float GravityAcc = 0.0f;
	FVector LastMoveVector = FVector::Zero;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	virtual void CheckGround() {};
	virtual void ChangeDir(EEngineDir _Dir) {};

	void SetMoveVector(const FVector& _MoveVector);
	void AddMoveVector(const FVector& _DirDelta);
	void SetJumpVector(const FVector& _JumpVector);
	void SetGravityVector(const FVector& _GravityVector);
	virtual void CalMoveVector(float _DeltaTime) {};
	virtual void CalJumpVector(float _DeltaTime) {};
	virtual void CalGravityVector(float _DeltaTime) {};
	void MoveUpdate(float _DeltaTime);

private:

};
#include "PreCompile.h"
#include "MovingActor.h"

AMovingActor::AMovingActor()
{

}

AMovingActor::~AMovingActor()
{

}

void AMovingActor::BeginPlay()
{
	Super::BeginPlay();
}

void AMovingActor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AMovingActor::SetMoveVector(const FVector& _MoveVector)
{
	MoveVector = _MoveVector;
}

void AMovingActor::AddMoveVector(const FVector& _DirDelta)
{
	MoveVector += _DirDelta * MoveAcc;
}

void AMovingActor::SetJumpVector(const FVector& _JumpVector)
{
	JumpVector = _JumpVector;
}

void AMovingActor::SetGravityVector(const FVector& _GravityVector)
{
	GravityVector = _GravityVector;
}

void AMovingActor::MoveUpdate(float _DeltaTime)
{
	CalMoveVector(_DeltaTime);
	CalJumpVector(_DeltaTime);
	CalGravityVector(_DeltaTime);

	LastMoveVector = FVector::Zero;
	LastMoveVector += MoveVector;
	LastMoveVector += JumpVector;
	LastMoveVector += GravityVector;

	AddActorLocation(LastMoveVector * _DeltaTime);
}
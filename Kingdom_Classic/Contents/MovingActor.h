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
	EGroundType CurGroundType = EGroundType::Plain;
	float Speed = 0.0f;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	virtual void CheckGround() {};
	virtual void ChangeDir(EEngineDir _Dir) {};

private:

};
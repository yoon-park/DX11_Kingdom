#pragma once

class AKingdomActor : public AActor
{
	GENERATED_BODY(AActor)

public:
	AKingdomActor();
	~AKingdomActor();

	AKingdomActor(const AKingdomActor& _Other) = delete;
	AKingdomActor(AKingdomActor&& _Other) noexcept = delete;
	AKingdomActor& operator=(const AKingdomActor& _Other) = delete;
	AKingdomActor& operator=(AKingdomActor&& _Other) noexcept = delete;

protected:
	EEngineDir PrevDir = EEngineDir::Right;
	EEngineDir CurDir = EEngineDir::Right;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	virtual void CheckGround() {};
	virtual void ChangeDir(EEngineDir _Dir) {};

private:

};
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
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	virtual bool IsGround();
	virtual void ChangeDir(EEngineDir _Dir) {};

private:

};
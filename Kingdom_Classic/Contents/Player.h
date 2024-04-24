#pragma once

class APlayer : public AActor
{
	GENERATED_BODY(AActor)

public:
	APlayer();
	~APlayer();

	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	UStateManager State;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer_Player;
	USpriteRenderer* Renderer_Horse;
	UCollision* CheckSpotNearby;
	float Speed = 0.0f;

	void DebugMessageFunction();

	// State
	void StateInit();

	void IdleStart();
	void WalkStart();
	void RunStart();
	void RearStart();
	void EatStart();
	void PayStart();

	void Idle(float _DeltaTime);
	void Walk(float _DeltaTime);
	void Run(float _DeltaTime);
	void Rear(float _DeltaTime);
	void Eat(float _DeltaTime);
	void Pay(float _DeltaTime);
};
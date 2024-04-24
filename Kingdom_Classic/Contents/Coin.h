#pragma once

class ACoin : public AActor
{
	GENERATED_BODY(AActor)

public:
	ACoin();
	~ACoin();

	ACoin(const ACoin& _Other) = delete;
	ACoin(ACoin&& _Other) noexcept = delete;
	ACoin& operator=(const ACoin& _Other) = delete;
	ACoin& operator=(ACoin&& _Other) noexcept = delete;

	UStateManager State;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;
	UCollision* Collision;
	float Speed = 0.0f;

	// State
	void StateInit();

	void IdleStart();
	void FallStart();
	void PayStart();

	void Idle(float _DeltaTime);
	void Fall(float _DeltaTime);
	void Pay(float _DeltaTime);
};
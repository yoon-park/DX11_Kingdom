#pragma once

class USpriteRenderer;

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
	USpriteRenderer* Renderer;
	float4 Color;

	void DebugMessageFunction();

	// State
	void StateInit();
	
	void Die(float _DeltaTime);
	
	void Idle(float _DeltaTime);
	
	void Jump(float _DeltaTime);
	
	void RunStart();
	void Run(float _DeltaTime);
};
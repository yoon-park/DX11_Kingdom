#pragma once

class ATool : public AActor
{
	GENERATED_BODY(AActor)

public:
	ATool();
	~ATool();

	ATool(const ATool& _Other) = delete;
	ATool(ATool&& _Other) noexcept = delete;
	ATool& operator=(const ATool& _Other) = delete;
	ATool& operator=(ATool&& _Other) noexcept = delete;

	UStateManager State;

	USpriteRenderer* GetRenderer()
	{
		return Renderer;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;
	float Inter_Blink = 0.1f;
	int Cnt_Blink = 8;

	// State
	void StateInit();

	void InactiveStart();
	void CreateStart();
	void ActiveStart();

	void Inactive(float _DeltaTime);
	void Create(float _DeltaTime);
	void Active(float _DeltaTime);

	void CreateEnd();
};
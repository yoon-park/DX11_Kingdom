#pragma once

class USpriteRenderer;

class AWall : public AActor
{
	GENERATED_BODY(AActor)

public:
	AWall();
	~AWall();

	AWall(const AWall& _Other) = delete;
	AWall(AWall&& _Other) noexcept = delete;
	AWall& operator=(const AWall& _Other) = delete;
	AWall& operator=(AWall&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;
};
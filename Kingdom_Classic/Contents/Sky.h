#pragma once

class USpriteRenderer;

class ASky : public AActor
{
	GENERATED_BODY(AActor)

public:
	ASky();
	~ASky();

	ASky(const ASky& _Other) = delete;
	ASky(ASky&& _Other) noexcept = delete;
	ASky& operator=(const ASky& _Other) = delete;
	ASky& operator=(ASky&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;
};
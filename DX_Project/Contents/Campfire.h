#pragma once

class USpriteRenderer;

class ACampfire : public AActor
{
	GENERATED_BODY(AActor)

public:
	ACampfire();
	~ACampfire();

	ACampfire(const ACampfire& _Other) = delete;
	ACampfire(ACampfire&& _Other) noexcept = delete;
	ACampfire& operator=(const ACampfire& _Other) = delete;
	ACampfire& operator=(ACampfire&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;
	float4 Color;
};
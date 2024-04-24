#pragma once

class USpriteRenderer;

class ABack3 : public AActor
{
	GENERATED_BODY(AActor)

public:
	ABack3();
	~ABack3();

	ABack3(const ABack3& _Other) = delete;
	ABack3(ABack3&& _Other) noexcept = delete;
	ABack3& operator=(const ABack3& _Other) = delete;
	ABack3& operator=(ABack3&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;
	float4 Color;
};
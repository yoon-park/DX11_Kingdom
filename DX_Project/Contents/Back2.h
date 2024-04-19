#pragma once

class USpriteRenderer;

class ABack2 : public AActor
{
	GENERATED_BODY(AActor)

public:
	ABack2();
	~ABack2();

	ABack2(const ABack2& _Other) = delete;
	ABack2(ABack2&& _Other) noexcept = delete;
	ABack2& operator=(const ABack2& _Other) = delete;
	ABack2& operator=(ABack2&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;
	float4 Color;
};
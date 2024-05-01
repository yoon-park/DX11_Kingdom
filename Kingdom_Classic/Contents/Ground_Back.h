#pragma once

class USpriteRenderer;

class AGround_Back : public AActor
{
	GENERATED_BODY(AActor)

public:
	AGround_Back();
	~AGround_Back();

	AGround_Back(const AGround_Back& _Other) = delete;
	AGround_Back(AGround_Back&& _Other) noexcept = delete;
	AGround_Back& operator=(const AGround_Back& _Other) = delete;
	AGround_Back& operator=(AGround_Back&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;
	float4 Color;
};
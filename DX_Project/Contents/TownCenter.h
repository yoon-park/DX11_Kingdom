#pragma once

class USpriteRenderer;

class ATownCenter : public AActor
{
	GENERATED_BODY(AActor)

public:
	ATownCenter();
	~ATownCenter();

	ATownCenter(const ATownCenter& _Other) = delete;
	ATownCenter(ATownCenter&& _Other) noexcept = delete;
	ATownCenter& operator=(const ATownCenter& _Other) = delete;
	ATownCenter& operator=(ATownCenter&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;
	float4 Color;
};
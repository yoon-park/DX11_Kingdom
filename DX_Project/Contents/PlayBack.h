#pragma once

class USpriteRenderer;

class APlayBack : public AActor
{
	GENERATED_BODY(AActor)

public:
	APlayBack();
	~APlayBack();

	APlayBack(const APlayBack& _Other) = delete;
	APlayBack(APlayBack&& _Other) noexcept = delete;
	APlayBack& operator=(const APlayBack& _Other) = delete;
	APlayBack& operator=(APlayBack&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;
	float4 Color;
};
#pragma once

class USpriteRenderer;

class APlayBackBack : public AActor
{
	GENERATED_BODY(AActor)

public:
	APlayBackBack();
	~APlayBackBack();

	APlayBackBack(const APlayBackBack& _Other) = delete;
	APlayBackBack(APlayBackBack&& _Other) noexcept = delete;
	APlayBackBack& operator=(const APlayBackBack& _Other) = delete;
	APlayBackBack& operator=(APlayBackBack&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;
	float4 Color;
};
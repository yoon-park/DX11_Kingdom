#pragma once

class ATitleLogo : public AActor
{
	GENERATED_BODY(AActor)

public:
	ATitleLogo();
	~ATitleLogo();

	ATitleLogo(const ATitleLogo& _Other) = delete;
	ATitleLogo(ATitleLogo&& _Other) noexcept = delete;
	ATitleLogo& operator=(const ATitleLogo& _Other) = delete;
	ATitleLogo& operator=(ATitleLogo&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void RendererOn();
	void RendererOff();

private:
	URenderer* Renderer = nullptr;
	float4 Color = FVector::Red;
};
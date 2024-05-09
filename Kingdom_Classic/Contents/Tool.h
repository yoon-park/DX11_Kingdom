#pragma once

class ATool : public AActor
{
	GENERATED_BODY(AActor)

public:
	ATool();
	~ATool();

	ATool(const ATool& _Other) = delete;
	ATool(ATool&& _Other) noexcept = delete;
	ATool& operator=(const ATool& _Other) = delete;
	ATool& operator=(ATool&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;
	UCollision* Collision;

};
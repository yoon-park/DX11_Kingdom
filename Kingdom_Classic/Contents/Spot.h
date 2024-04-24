#pragma once

class ASpot : public AActor
{
	GENERATED_BODY(AActor)

public:
	ASpot();
	~ASpot();

	ASpot(const ASpot& _Other) = delete;
	ASpot(ASpot&& _Other) noexcept = delete;
	ASpot& operator=(const ASpot& _Other) = delete;
	ASpot& operator=(ASpot&& _Other) noexcept = delete;

protected:
	ESpotUpgrade CurTier = ESpotUpgrade::Tier0;
	UDefaultSceneComponent* Root;
	UCollision* CheckPlayerNearby;

	USpriteRenderer* Renderer_Coin00;
	USpriteRenderer* Renderer_Coin01;
	USpriteRenderer* Renderer_Coin02;
	USpriteRenderer* Renderer_Coin03;
	USpriteRenderer* Renderer_Coin04;
	USpriteRenderer* Renderer_Coin05;
	USpriteRenderer* Renderer_Coin06;
	USpriteRenderer* Renderer_Coin07;
	USpriteRenderer* Renderer_Coin08;
	USpriteRenderer* Renderer_Coin09;
	USpriteRenderer* Renderer_Coin10;
	USpriteRenderer* Renderer_Coin11;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	virtual void Upgrade();

private:

};
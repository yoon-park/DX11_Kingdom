#pragma once
#include "MovingActor.h"

class ANPC : public AMovingActor
{
	GENERATED_BODY(AMovingActor)

public:
	ANPC();
	~ANPC();

	ANPC(const ANPC& _Other) = delete;
	ANPC(ANPC&& _Other) noexcept = delete;
	ANPC& operator=(const ANPC& _Other) = delete;
	ANPC& operator=(ANPC&& _Other) noexcept = delete;

protected:
	USpriteRenderer* Renderer;
	UCollision* Collision;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void ChangeDir(EEngineDir _Dir);

private:

};
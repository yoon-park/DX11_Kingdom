#pragma once
#include "Monster.h"

class ABreeder : public AMonster
{
	GENERATED_BODY(AMonster)

public:
	ABreeder();
	~ABreeder();

	ABreeder(const ABreeder& _Other) = delete;
	ABreeder(ABreeder&& _Other) noexcept = delete;
	ABreeder& operator=(const ABreeder& _Other) = delete;
	ABreeder& operator=(ABreeder&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CheckGround();

private:

};
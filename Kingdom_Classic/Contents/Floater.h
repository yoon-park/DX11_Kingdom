#pragma once
#include "Monster.h"

class AFloater : public AMonster
{
	GENERATED_BODY(AMonster)

public:
	AFloater();
	~AFloater();

	AFloater(const AFloater& _Other) = delete;
	AFloater(AFloater&& _Other) noexcept = delete;
	AFloater& operator=(const AFloater& _Other) = delete;
	AFloater& operator=(AFloater&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CheckGround();

private:

};
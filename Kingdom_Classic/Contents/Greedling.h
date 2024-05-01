#pragma once
#include "Monster.h"

class AGreedling : public AMonster
{
	GENERATED_BODY(AMonster)

public:
	AGreedling();
	~AGreedling();

	AGreedling(const AGreedling& _Other) = delete;
	AGreedling(AGreedling&& _Other) noexcept = delete;
	AGreedling& operator=(const AGreedling& _Other) = delete;
	AGreedling& operator=(AGreedling&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CheckGround();

private:

};
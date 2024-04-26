#pragma once
#include "KingdomActor.h"

class AMonster : public AKingdomActor
{
	GENERATED_BODY(AKingdomActor)

public:
	AMonster();
	~AMonster();

	AMonster(const AMonster& _Other) = delete;
	AMonster(AMonster&& _Other) noexcept = delete;
	AMonster& operator=(const AMonster& _Other) = delete;
	AMonster& operator=(AMonster&& _Other) noexcept = delete;

protected:

private:

};
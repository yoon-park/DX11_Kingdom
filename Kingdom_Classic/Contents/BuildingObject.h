#pragma once

class ABuildingObject : public AActor
{
	GENERATED_BODY(AActor)

public:
	ABuildingObject();
	~ABuildingObject();

	ABuildingObject(const ABuildingObject& _Other) = delete;
	ABuildingObject(ABuildingObject&& _Other) noexcept = delete;
	ABuildingObject& operator=(const ABuildingObject& _Other) = delete;
	ABuildingObject& operator=(ABuildingObject&& _Other) noexcept = delete;

	UStateManager State;

	EBuildingObjectType GetType()
	{
		return Type;
	}

	int GetRequiredCoin()
	{
		return RequiredCoin;
	}

	int GetLeftCoin()
	{
		return LeftCoin;
	}

	FVector GetCoinLocation(int _Index)
	{
		return Renderer_Coins[_Index]->GetWorldPosition();
	}

protected:
	UDefaultSceneComponent* Root;
	UCollision* Collision_Check;

	EBuildingObjectType Type = EBuildingObjectType::None;
	bool IsPlayerContact = false;
	int RequiredCoin = 1;
	int LeftCoin = RequiredCoin;

	std::vector<USpriteRenderer*> Renderer_Coins;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CheckPlayer();
	void CheckLeftCoin();

	void SetCoinIndicatorActive(bool _Active, int _CoinNum);
	virtual void SetCoinIndicatorLocation() {};

private:

};
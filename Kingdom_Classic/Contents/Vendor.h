#pragma once

class AVendor : public AActor
{
	GENERATED_BODY(AActor)

public:
	AVendor();
	~AVendor();

	AVendor(const AVendor& _Other) = delete;
	AVendor(AVendor&& _Other) noexcept = delete;
	AVendor& operator=(const AVendor& _Other) = delete;
	AVendor& operator=(AVendor&& _Other) noexcept = delete;

	UStateManager State;

protected:
	UDefaultSceneComponent* Root;
	UCollision* Collision_Active;

	bool IsPlayerContact = false;
	int RequiredCoin = 1;
	int LeftCoin = RequiredCoin;

	std::vector<USpriteRenderer*> Renderer_Coins;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CheckPlayer();
	void CheckLeftCoin();

	void SetCoinIndicatorActive(bool _Active, int _CoinNum = 12);
	virtual void SetCoinIndicatorLocation() {};

	// State
	virtual void StateInit();

	virtual void InactiveIdleStart();
	virtual void ActiveIdleStart();
	virtual void BuyStart();

	virtual void InactiveIdle(float _DeltaTime);
	virtual void ActiveIdle(float _DeltaTime);
	virtual void Buy(float _DeltaTime);

private:

};
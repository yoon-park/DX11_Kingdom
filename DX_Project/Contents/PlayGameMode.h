#pragma once

class APlayer;

class APlayGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	APlayGameMode();
	~APlayGameMode();

	APlayGameMode(const APlayGameMode& _Other) = delete;
	APlayGameMode(APlayGameMode&& _Other) noexcept = delete;
	APlayGameMode& operator=(const APlayGameMode& _Other) = delete;
	APlayGameMode& operator=(APlayGameMode&& _Other) noexcept = delete;

protected:
	void SetMainPlayer(std::shared_ptr<APlayer> _Player);

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<APlayer> MainPlayer;
};
#pragma once

class APlayer;
class ATownCenter;

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

	static std::shared_ptr<APlayer> MainPlayer;
	static std::shared_ptr<ATownCenter> MyKingdom;

protected:
	void SetMainPlayer(std::shared_ptr<APlayer> _Player);
	void SetMyKingdom(std::shared_ptr<ATownCenter> _MyKingdom);

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CameraUpdate();

private:

};
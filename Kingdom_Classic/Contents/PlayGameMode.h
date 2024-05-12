#pragma once

class APlayer;
class ATownCenter;
class UContentsTime;

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
	static std::shared_ptr<UContentsTime> ContentsTimer;
	static std::map<int, std::list<std::shared_ptr<AActor>>> NPCs;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CameraUpdate();

private:

};
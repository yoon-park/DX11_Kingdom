#pragma once

class UContentsTime : public AActor
{
public:
	UContentsTime();
	~UContentsTime();

	UContentsTime(const UContentsTime& _Other) = delete;
	UContentsTime(UContentsTime&& _Other) noexcept = delete;
	UContentsTime& operator=(const UContentsTime& _Other) = delete;
	UContentsTime& operator=(UContentsTime&& _Other) noexcept = delete;

	float GetCount()
	{
		return Count;
	}

	int GetDate()
	{
		return Date;
	}

	bool GetIsDay()
	{
		return IsDay;
	}

	void ResetCount()
	{
		Count = 0.0f;
	}

	void Update();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	float Count = 0.0f;
	int Date = 1;
	bool IsDay = true;
};
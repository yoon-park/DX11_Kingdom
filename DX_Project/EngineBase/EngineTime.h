#pragma once

class UEngineTime
{
public:
	UEngineTime();
	~UEngineTime();

	UEngineTime(const UEngineTime& _Other) = delete;
	UEngineTime(UEngineTime&& _Other) noexcept = delete;
	UEngineTime& operator=(const UEngineTime& _Other) = delete;
	UEngineTime& operator=(UEngineTime&& _Other) noexcept = delete;

	double GetDeltaTime()
	{
		return DeltaTime;
	}

	void TimeCheckStart();
	float TimeCheck();

protected:

private:
	__int64 Count64;
	LARGE_INTEGER Count;
	LARGE_INTEGER PrevTime;
	LARGE_INTEGER CurTime;
	double dCount;
	double DeltaTime;
};
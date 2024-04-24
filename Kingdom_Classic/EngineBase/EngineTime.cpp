#include "PreCompile.h"
#include "EngineTime.h"

UEngineTime::UEngineTime() 
{
	TimeCheckStart();
}

UEngineTime::~UEngineTime() 
{

}

void UEngineTime::TimeCheckStart()
{
	QueryPerformanceFrequency(&Count);
	QueryPerformanceCounter(&PrevTime);

	dCount = static_cast<double>(Count.QuadPart);
}

float UEngineTime::TimeCheck()
{
	QueryPerformanceCounter(&CurTime);

	__int64 Tick = (CurTime.QuadPart - PrevTime.QuadPart);
	double dTick = static_cast<double>(Tick);

	DeltaTime = dTick / dCount;
	PrevTime.QuadPart = CurTime.QuadPart;
	
	return static_cast<float>(DeltaTime);
}
#include "PreCompile.h"
#include "ContentsTime.h"

UContentsTime::UContentsTime()
{

}

UContentsTime::~UContentsTime()
{

}

void UContentsTime::BeginPlay()
{
	ResetCount();
}

void UContentsTime::Tick(float _DeltaTime)
{
	Update();

	Count += _DeltaTime;
}

void UContentsTime::Update()
{
	if (Count >= 30.0f)
	{
		if (IsDay == true)
		{
			IsDay = false;
		}
		else
		{
			IsDay = true;
			Date += 1;
		}

		ResetCount();
	}
}
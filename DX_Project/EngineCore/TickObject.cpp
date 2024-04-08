#include "PreCompile.h"
#include "TickObject.h"

UTickObject::UTickObject()
{

}

UTickObject::~UTickObject()
{

}

void UTickObject::BeginPlay()
{

}

void UTickObject::Tick(float _DeltaTime)
{
	for (size_t i = 0; i < Callbacks.size(); i++)
	{
		if (Callbacks[i] == nullptr)
		{
			continue;
		}

		Callbacks[i]->Time -= _DeltaTime;
		if (Callbacks[i]->Time <= 0)
		{
			if (Callbacks[i]->Callback == nullptr)
			{
				MsgBoxAssert("함수가 세팅되지 않은 딜레이 콜백기능을 사용하려 했습니다.");
			}

			Callbacks[i]->Callback();
			Callbacks[i] = nullptr;
		}
	}
}

void UTickObject::LevelStart(ULevel* _PrevLevel)
{

}

void UTickObject::LevelEnd(ULevel* _NextLevel)
{

}
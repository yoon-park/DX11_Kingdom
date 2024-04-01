#include "PreCompile.h"
#include "Level.h"

#include "GameMode.h"

bool ULevel::IsActorConstructor = true;

ULevel::ULevel()
{

}

ULevel::~ULevel()
{

}

void ULevel::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	for (std::pair<const int, std::list<std::shared_ptr<AActor>>>& TickGroup : Actors)
	{
		std::list<std::shared_ptr<AActor>>& GroupActors = TickGroup.second;

		for (std::shared_ptr<AActor> Actor : GroupActors)
		{
			Actor->Tick(_DeltaTime);
		}
	}
}

void ULevel::PushActor(std::shared_ptr<AActor> _Actor)
{
	if (_Actor == nullptr)
	{
		MsgBoxAssert("��������� ���� ���͸� ������ �߰��Ϸ� �߽��ϴ�.");
		return;
	}

	_Actor->SetWorld(this);
	_Actor->BeginPlay();

	Actors[_Actor->GetOrder()].push_back(_Actor);
}
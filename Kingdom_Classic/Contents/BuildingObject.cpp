#include "PreCompile.h"
#include "BuildingObject.h"

#include "PlayGameMode.h"
#include "Player.h"

ABuildingObject::ABuildingObject()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	SetRoot(Root);
}

ABuildingObject::~ABuildingObject()
{

}

void ABuildingObject::BeginPlay()
{
	Super::BeginPlay();
}

void ABuildingObject::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ABuildingObject::CheckPlayer()
{
	Collision_Check->CollisionEnter(ECollisionOrder::Horse, [=](std::shared_ptr<UCollision> _Collision)
		{
			IsPlayerContact = true;
			return;
		}
	);

	Collision_Check->CollisionStay(ECollisionOrder::Horse, [=](std::shared_ptr<UCollision> _Collision)
		{
			IsPlayerContact = true;
			return;
		}
	);

	Collision_Check->CollisionExit(ECollisionOrder::Horse, [=](std::shared_ptr<UCollision> _Collision)
		{
			IsPlayerContact = false;
			return;
		}
	);
}

void ABuildingObject::CheckLeftCoin()
{
	if (
		IsPlayerContact == false ||
		APlayGameMode::MainPlayer->GetIsPaying() == false
		)
	{
		LeftCoin = RequiredCoin;
	}
	else if (
		IsPlayerContact == true &&
		APlayGameMode::MainPlayer->GetIsPaying() == true &&
		APlayGameMode::MainPlayer->GetCurCoin()->State.GetCurStateName() == "Wait"
		)
	{
		LeftCoin -= 1;
	}
}

void ABuildingObject::SetCoinIndicatorActive(bool _Active, int _CoinNum)
{
	if (_Active == true)
	{
		for (int i = 0; i < _CoinNum; i++)
		{
			Renderer_Coins[i]->SetActive(true);
		}
	}
	else
	{
		for (int i = 0; i < _CoinNum; i++)
		{
			Renderer_Coins[i]->SetActive(false);
		}
	}
}
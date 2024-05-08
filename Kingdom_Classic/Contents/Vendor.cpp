#include "PreCompile.h"
#include "Vendor.h"

#include "PlayGameMode.h"
#include "Player.h"

AVendor::AVendor()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	for (int i = 0; i < 12; i++)
	{
		USpriteRenderer* Coin = CreateDefaultSubObject<USpriteRenderer>("Renderer");
		Coin->SetupAttachment(Root);
		Coin->SetActive(false);
		Renderer_Coins.push_back(Coin);
	}

	Collision_Active = CreateDefaultSubObject<UCollision>("Collision_Active");
	Collision_Active->SetupAttachment(Root);
	Collision_Active->SetScale(FVector(80.0f, 80.0f, 100.0f));
	Collision_Active->SetPosition(FVector(0.0f, -24.0f, 0.0f));
	Collision_Active->SetCollisionGroup(ECollisionOrder::Spot);
	Collision_Active->SetCollisionType(ECollisionType::Rect);

	SetRoot(Root);
}

AVendor::~AVendor()
{

}

void AVendor::BeginPlay()
{

}

void AVendor::Tick(float _DeltaTime)
{

}

void AVendor::CheckPlayer()
{
	Collision_Active->CollisionEnter(ECollisionOrder::Horse, [=](std::shared_ptr<UCollision> _Collision)
		{
			IsPlayerContact = true;
			return;
		}
	);

	Collision_Active->CollisionStay(ECollisionOrder::Horse, [=](std::shared_ptr<UCollision> _Collision)
		{
			IsPlayerContact = true;
			return;
		}
	);

	Collision_Active->CollisionExit(ECollisionOrder::Horse, [=](std::shared_ptr<UCollision> _Collision)
		{
			IsPlayerContact = false;
			return;
		}
	);
}

void AVendor::CheckLeftCoin()
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

void AVendor::SetCoinIndicatorActive(bool _Active, int _CoinNum)
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

void AVendor::StateInit()
{

}

void AVendor::InactiveIdleStart()
{

}

void AVendor::ActiveIdleStart()
{

}

void AVendor::BuyStart()
{

}

void AVendor::InactiveIdle(float _DeltaTime)
{

}

void AVendor::ActiveIdle(float _DeltaTime)
{

}

void AVendor::Buy(float _DeltaTime)
{

}
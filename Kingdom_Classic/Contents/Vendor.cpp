#include "PreCompile.h"
#include "Vendor.h"

#include "PlayGameMode.h"
#include "Player.h"

AVendor::AVendor()
{
	{
		Renderer_NPC = CreateDefaultSubObject<USpriteRenderer>("Renderer_NPC");
		Renderer_NPC->SetupAttachment(Root);

		Renderer_Vendor = CreateDefaultSubObject<USpriteRenderer>("Renderer_Vendor");
		Renderer_Vendor->SetupAttachment(Root);

		for (int i = 0; i < 3; i++)
		{
			USpriteRenderer* Coin = CreateDefaultSubObject<USpriteRenderer>("Renderer_Coin");
			Coin->SetupAttachment(Root);
			Coin->SetActive(false);
			Renderer_Coins.push_back(Coin);
		}
	}
	{
		Collision_Check = CreateDefaultSubObject<UCollision>("Collision_Active");
		Collision_Check->SetupAttachment(Root);
		Collision_Check->SetScale(FVector(80.0f, 80.0f, 100.0f));
		Collision_Check->SetPosition(FVector(0.0f, 0.0f, 0.0f));
		Collision_Check->SetCollisionGroup(ECollisionOrder::BuildingObject);
		Collision_Check->SetCollisionType(ECollisionType::Rect);
	}

	Type = EBuildingObjectType::Vendor;
}

AVendor::~AVendor()
{

}

void AVendor::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < 3; i++)
	{
		Renderer_Coins[i]->SetSprite("Coin_Indicator.png");
		Renderer_Coins[i]->SetAutoSize(1.0f, true);
		Renderer_Coins[i]->SetOrder(ERenderOrder::UI);
	}

	SetCoinIndicatorLocation();
	StateInit();
}

void AVendor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	SetDir();

	State.Update(_DeltaTime);
}

void AVendor::SetDir()
{
	FVector Diff = APlayGameMode::MainPlayer->GetActorLocation() - GetActorLocation();

	if (Diff.X < 0.0f)
	{
		Renderer_NPC->SetDir(EEngineDir::Left);
	}
	else
	{
		Renderer_NPC->SetDir(EEngineDir::Right);
	}
}

void AVendor::StateInit()
{
	{
		State.CreateState("Inactive");
		State.SetStartFunction("Inactive", std::bind(&AVendor::InactiveStart, this));
		State.SetUpdateFunction("Inactive", std::bind(&AVendor::Inactive, this, std::placeholders::_1));

		State.CreateState("Active");
		State.SetStartFunction("Active", std::bind(&AVendor::ActiveStart, this));
		State.SetUpdateFunction("Active", std::bind(&AVendor::Active, this, std::placeholders::_1));

		State.CreateState("Buy");
		State.SetStartFunction("Buy", std::bind(&AVendor::BuyStart, this));
		State.SetUpdateFunction("Buy", std::bind(&AVendor::Buy, this, std::placeholders::_1));
		State.SetEndFunction("Buy", std::bind(&AVendor::BuyEnd, this));
	}

	State.ChangeState("Inactive");
}

void AVendor::InactiveStart()
{
	SetCoinIndicatorActive(false, RequiredCoin);
}

void AVendor::ActiveStart()
{
	SetCoinIndicatorActive(true, RequiredCoin);
}

void AVendor::BuyStart()
{

}

void AVendor::Inactive(float _DeltaTime)
{
	if (IsPlayerContact == true)
	{
		State.ChangeState("Active");
		return;
	}

	CheckPlayer();
}

void AVendor::Active(float _DeltaTime)
{
	if (IsPlayerContact == false)
	{
		State.ChangeState("Inactive");
		return;
	}

	if (LeftCoin == 0)
	{
		State.ChangeState("Buy");
		return;
	}

	CheckPlayer();
	CheckLeftCoin();
}

void AVendor::Buy(float _DeltaTime)
{

}

void AVendor::BuyEnd()
{
	LeftCoin = RequiredCoin;
}
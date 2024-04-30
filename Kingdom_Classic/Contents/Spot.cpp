#include "PreCompile.h"
#include "Spot.h"

#include "PlayGameMode.h"
#include "Player.h"

ASpot::ASpot()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	for (int i = 0; i < 12; i++)
	{
		USpriteRenderer* Coin = CreateDefaultSubObject<USpriteRenderer>("Renderer");
		Coin->SetupAttachment(Root);
		Coin->SetActive(false);
		Renderer_Coins.push_back(Coin);
	}

	Collision_Update = CreateDefaultSubObject<UCollision>("Collision_Update");
	Collision_Update->SetupAttachment(Root);
	Collision_Update->SetScale(FVector(80.0f, 80.0f, 100.0f));
	Collision_Update->AddPosition(FVector(0.0f, -24.0f, 0.0f));
	Collision_Update->SetCollisionGroup(ECollisionOrder::Spot);
	Collision_Update->SetCollisionType(ECollisionType::Rect);

	SetRoot(Root);
}

ASpot::~ASpot()
{

}

void ASpot::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < 12; i++)
	{
		Renderer_Coins[i]->SetSprite("Coin_Indicator.png");
		Renderer_Coins[i]->SetAutoSize(1.0f, true);
		Renderer_Coins[i]->SetOrder(ERenderOrder::UI);
	}

	Upgrade();
}

void ASpot::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	CheckPlayer();
	CheckLeftCoin();
}

void ASpot::CheckPlayer()
{
	Collision_Update->CollisionStay(ECollisionOrder::Horse, [=](std::shared_ptr<UCollision> _Collision)
		{
			for (int i = 0; i < RequiredCoin; i++)
			{
				Renderer_Coins[i]->SetActive(true);
			}

			return;
		}
	);

	Collision_Update->CollisionExit(ECollisionOrder::Horse, [=](std::shared_ptr<UCollision> _Collision)
		{
			for (int i = 0; i < 12; i++)
			{
				Renderer_Coins[i]->SetActive(false);
			}

			return;
		}
	);
}

void ASpot::CheckLeftCoin()
{
	if (IsUpgradable == true && LeftCoin == 0)
	{
		Upgrade();
		IsUpdateDone = true;
		return;
	}

	if (APlayGameMode::MainPlayer->GetIsPaying() == true)
	{
		if (APlayGameMode::MainPlayer->GetIsPayDone() == true)
		{
			LeftCoin -= 1;
			APlayGameMode::MainPlayer->SetIsPayDone(false);
		}
	}
	else
	{
		LeftCoin = RequiredCoin;
	}
}

void ASpot::Upgrade()
{
	LeftCoin = RequiredCoin;

	float4 InitLocation = GetActorLocation();

	switch (RequiredCoin)
	{
	case 1:
	{
		Renderer_Coins[0]->SetPosition(InitLocation + float4({ 0.0f, 0.0f, 0.0f, 0.0f }));
		break;
	}
	case 3:
	{
		Renderer_Coins[0]->SetPosition(InitLocation + float4({ -15.0f, 0.0f, 0.0f, 0.0f }));
		Renderer_Coins[1]->SetPosition(InitLocation + float4({ 0.0f, 0.0f, 0.0f, 0.0f }));
		Renderer_Coins[2]->SetPosition(InitLocation + float4({ 15.0f, 0.0f, 0.0f, 0.0f }));
		break;
	}
	case 6:
	{
		Renderer_Coins[0]->AddPosition({ -15.0f, 0.0f, 0.0f, 0.0f });
		Renderer_Coins[1]->AddPosition({ 0.0f, 0.0f, 0.0f, 0.0f });
		Renderer_Coins[2]->AddPosition({ 15.0f, 0.0f, 0.0f, 0.0f });
		Renderer_Coins[3]->AddPosition({ -15.0f, 15.0f, 0.0f, 0.0f });
		Renderer_Coins[4]->AddPosition({ 0.0f, 15.0f, 0.0f, 0.0f });
		Renderer_Coins[5]->AddPosition({ 15.0f, 15.0f, 0.0f, 0.0f });
		break;
	}
	case 9:
	{
		Renderer_Coins[0]->AddPosition({ -20.0f, 0.0f, 0.0f, 0.0f });
		Renderer_Coins[1]->AddPosition({ -5.0f, 0.0f, 0.0f, 0.0f });
		Renderer_Coins[2]->AddPosition({ 5.0f, 0.0f, 0.0f, 0.0f });
		Renderer_Coins[3]->AddPosition({ 20.0f, 0.0f, 0.0f, 0.0f });
		Renderer_Coins[4]->AddPosition({ -30.0f, 15.0f, 0.0f, 0.0f });
		Renderer_Coins[5]->AddPosition({ -15.0f, 15.0f, 0.0f, 0.0f });
		Renderer_Coins[6]->AddPosition({ 0.0f, 15.0f, 0.0f, 0.0f });
		Renderer_Coins[7]->AddPosition({ 15.0f, 15.0f, 0.0f, 0.0f });
		Renderer_Coins[8]->AddPosition({ 30.0f, 15.0f, 0.0f, 0.0f });
		break;
	}
	default:
		break;
	}
}
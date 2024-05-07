#include "PreCompile.h"
#include "TownCenter.h"

ATownCenter::ATownCenter()
{
	{
		Renderer_Campfire = CreateDefaultSubObject<USpriteRenderer>("Renderer_Campfire");
		Renderer_Campfire->SetupAttachment(Root);

		Renderer_Banner = CreateDefaultSubObject<USpriteRenderer>("Renderer_Banner");
		Renderer_Banner->SetupAttachment(Root);
		Renderer_Banner->SetActive(false);

		Renderer_Castle = CreateDefaultSubObject<USpriteRenderer>("Renderer_Castle");
		Renderer_Castle->SetupAttachment(Root);

		for (int i = 0; i < 4; i++)
		{
			USpriteRenderer* Renderer_Wall = CreateDefaultSubObject<USpriteRenderer>("Renderer_Wall");
			Renderer_Wall->SetupAttachment(Root);
			Renderer_Wall->SetActive(false);
			Renderer_Walls.push_back(Renderer_Wall);
		}
	}

	SkipUpgradeProgress = true;
}

ATownCenter::~ATownCenter()
{

}

void ATownCenter::BeginPlay()
{
	Super::BeginPlay();

	{
		Renderer_Campfire->SetSprite("Campfire_00.png");
		Renderer_Campfire->SetAutoSize(1.0f, true);
		Renderer_Campfire->SetPosition({ 0.0f, -35.0f, 0.0f, 0.0f });
		Renderer_Campfire->SetOrder(ERenderOrder::GroundObject);

		Renderer_Banner->SetSprite("Banner_02.png");
		Renderer_Banner->SetAutoSize(1.0f, true);
		Renderer_Banner->SetPosition({ -42.0f, -35.0f, 0.0f, 0.0f });
		Renderer_Banner->SetOrder(ERenderOrder::BackObject);

		Renderer_Castle->SetSprite("TownCenter_00.png");
		Renderer_Castle->SetAutoSize(1.0f, true);
		Renderer_Castle->SetOrder(ERenderOrder::BackObject);

		Renderer_Walls[0]->SetSprite("WoodenWall.png");
		Renderer_Walls[0]->SetAutoSize(1.0f, true);
		Renderer_Walls[0]->SetPosition({ -216.0f, -48.0f, 0.0f, 0.0f });
		Renderer_Walls[0]->SetOrder(ERenderOrder::BackObject);
		Renderer_Walls[0]->SetDir(EEngineDir::Left);

		Renderer_Walls[1]->SetSprite("WoodenWall.png");
		Renderer_Walls[1]->SetAutoSize(1.0f, true);
		Renderer_Walls[1]->SetPosition({ -73.0f, -48.0f, 0.0f, 0.0f });
		Renderer_Walls[1]->SetOrder(ERenderOrder::BackObject);

		Renderer_Walls[2]->SetSprite("WoodenWall.png");
		Renderer_Walls[2]->SetAutoSize(1.0f, true);
		Renderer_Walls[2]->SetPosition({ 73.0f, -48.0f, 0.0f, 0.0f });
		Renderer_Walls[2]->SetOrder(ERenderOrder::BackObject);
		Renderer_Walls[2]->SetDir(EEngineDir::Left);

		Renderer_Walls[3]->SetSprite("WoodenWall.png");
		Renderer_Walls[3]->SetAutoSize(1.0f, true);
		Renderer_Walls[3]->SetPosition({ 216.0f, -48.0f, 0.0f, 0.0f });
		Renderer_Walls[3]->SetOrder(ERenderOrder::BackObject);
	}
	{
		float4 ImageScale = UContentsConstValue::MapTexScale;
		float4 InitLocation = { ImageScale.hX(), -ImageScale.hY(), 0.0f };

		InnerWall_L = GetWorld()->SpawnActor<AWall>("InnerWall_L", EObjectOrder::Building);
		InnerWall_L->SetActorLocation(InitLocation + float4{-283.0f, 36.0f, 100.0f});
		InnerWall_L->SetDir(EEngineDir::Left);

		InnerWall_R = GetWorld()->SpawnActor<AWall>("InnerWall_R", EObjectOrder::Building);
		InnerWall_R->SetActorLocation(InitLocation + float4{283.0f, 36.0f, 100.0f});
	}
}

void ATownCenter::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ATownCenter::SetCoinIndicatorLocation()
{
	switch (RequiredCoin)
	{
	case 1:
	{
		Renderer_Coins[0]->SetPosition({ 0.0f, 0.0f, 0.0f, 0.0f });
		break;
	}
	case 3:
	{
		Renderer_Coins[0]->SetPosition({ -15.0f, 0.0f, 0.0f, 0.0f });
		Renderer_Coins[1]->SetPosition({ 0.0f, 0.0f, 0.0f, 0.0f });
		Renderer_Coins[2]->SetPosition({ 15.0f, 0.0f, 0.0f, 0.0f });
		break;
	}
	case 6:
	{
		Renderer_Coins[0]->SetPosition({ -15.0f, 0.0f, 0.0f, 0.0f });
		Renderer_Coins[1]->SetPosition({ 0.0f, 0.0f, 0.0f, 0.0f });
		Renderer_Coins[2]->SetPosition({ 15.0f, 0.0f, 0.0f, 0.0f });
		Renderer_Coins[3]->SetPosition({ -15.0f, 15.0f, 0.0f, 0.0f });
		Renderer_Coins[4]->SetPosition({ 0.0f, 15.0f, 0.0f, 0.0f });
		Renderer_Coins[5]->SetPosition({ 15.0f, 15.0f, 0.0f, 0.0f });
		break;
	}
	case 9:
	{
		Renderer_Coins[0]->SetPosition({ -23.0f, 0.0f, 0.0f, 0.0f });
		Renderer_Coins[1]->SetPosition({ -8.0f, 0.0f, 0.0f, 0.0f });
		Renderer_Coins[2]->SetPosition({ 8.0f, 0.0f, 0.0f, 0.0f });
		Renderer_Coins[3]->SetPosition({ 23.0f, 0.0f, 0.0f, 0.0f });
		Renderer_Coins[4]->SetPosition({ -30.0f, 15.0f, 0.0f, 0.0f });
		Renderer_Coins[5]->SetPosition({ -15.0f, 15.0f, 0.0f, 0.0f });
		Renderer_Coins[6]->SetPosition({ 0.0f, 15.0f, 0.0f, 0.0f });
		Renderer_Coins[7]->SetPosition({ 15.0f, 15.0f, 0.0f, 0.0f });
		Renderer_Coins[8]->SetPosition({ 30.0f, 15.0f, 0.0f, 0.0f });
		break;
	}
	default:
		break;
	}
}

void ATownCenter::SettingUpgrade()
{
	switch (CurTier)
	{
	case ESpotUpgrade::Tier0:
	{
		CurTier = ESpotUpgrade::Tier1;
		Renderer_Campfire->SetSprite("Campfire_01.png");
		RequiredCoin = 3;
		break;
	}
	case ESpotUpgrade::Tier1:
	{
		CurTier = ESpotUpgrade::Tier2;
		Renderer_Campfire->SetSprite("Campfire_02.png");
		Renderer_Banner->SetActive(true);
		Renderer_Castle->SetSprite("TownCenter_02.png");
		RequiredCoin = 6;
		SkipUpgradeProgress = false;
		break;
	}
	case ESpotUpgrade::Tier2:
	{
		CurTier = ESpotUpgrade::Tier3;
		Renderer_Campfire->SetSprite("Campfire_03.png");
		Renderer_Banner->SetSprite("Banner_03.png");
		Renderer_Banner->SetPosition({ 0.0f, 14.0f, 0.0f, 0.0f });
		Renderer_Castle->SetSprite("TownCenter_03.png");
		for (int i = 0; i < 4; i++)
		{
			Renderer_Walls[i]->SetActive(true);
		}
		RequiredCoin = 9;
		break;
	}
	case ESpotUpgrade::Tier3:
	{
		CurTier = ESpotUpgrade::Tier4;
		Renderer_Banner->SetPosition({ 0.0f, 12.0f, 0.0f, 0.0f });
		Renderer_Castle->SetSprite("TownCenter_04.png");
		for (int i = 0; i < 4; i++)
		{
			Renderer_Walls[i]->SetSprite("StoneWall.png");
		}
		RequiredCoin = 0;
		IsUpgradable = false;
		break;
	}
	default:
		break;
	}
}
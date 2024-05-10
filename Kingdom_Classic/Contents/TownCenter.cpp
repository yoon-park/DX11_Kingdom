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
		Renderer_Banner->SetOrder(ERenderOrder::Building);

		Renderer_Castle->SetSprite("TownCenter_00.png");
		Renderer_Castle->SetAutoSize(1.0f, true);
		Renderer_Castle->SetOrder(ERenderOrder::Building);

		Renderer_Walls[0]->SetSprite("WoodenWall.png");
		Renderer_Walls[0]->SetAutoSize(1.0f, true);
		Renderer_Walls[0]->SetPosition({ -216.0f, -48.0f, 0.0f, 0.0f });
		Renderer_Walls[0]->SetOrder(ERenderOrder::Back0);
		Renderer_Walls[0]->SetDir(EEngineDir::Left);

		Renderer_Walls[1]->SetSprite("WoodenWall.png");
		Renderer_Walls[1]->SetAutoSize(1.0f, true);
		Renderer_Walls[1]->SetPosition({ -73.0f, -48.0f, 0.0f, 0.0f });
		Renderer_Walls[1]->SetOrder(ERenderOrder::Back0);

		Renderer_Walls[2]->SetSprite("WoodenWall.png");
		Renderer_Walls[2]->SetAutoSize(1.0f, true);
		Renderer_Walls[2]->SetPosition({ 73.0f, -48.0f, 0.0f, 0.0f });
		Renderer_Walls[2]->SetOrder(ERenderOrder::Back0);
		Renderer_Walls[2]->SetDir(EEngineDir::Left);

		Renderer_Walls[3]->SetSprite("WoodenWall.png");
		Renderer_Walls[3]->SetAutoSize(1.0f, true);
		Renderer_Walls[3]->SetPosition({ 216.0f, -48.0f, 0.0f, 0.0f });
		Renderer_Walls[3]->SetOrder(ERenderOrder::Back0);
	}
	{
		InnerWall_L = GetWorld()->SpawnActor<AWall>("InnerWall_L", EObjectOrder::Building);
		InnerWall_L->SetActorLocation(UContentsConstValue::InitLocation + float4{-283.0f, 36.0f, 100.0f});
		InnerWall_L->SetDir(EEngineDir::Left);
		InnerWall_L->SetIsUpgradable(false);

		InnerWall_R = GetWorld()->SpawnActor<AWall>("InnerWall_R", EObjectOrder::Building);
		InnerWall_R->SetActorLocation(UContentsConstValue::InitLocation + float4{283.0f, 36.0f, 100.0f});
		InnerWall_R->SetIsUpgradable(false);

		Tower_L = GetWorld()->SpawnActor<ATower>("Tower_L", EObjectOrder::Building);
		Tower_L->SetActorLocation(UContentsConstValue::InitLocation + float4{ -900.0f, 54.0f, 100.0f });
		Tower_L->SetDir(EEngineDir::Left);
		Tower_L->SetIsUpgradable(false);

		Tower_R = GetWorld()->SpawnActor<ATower>("Tower_R", EObjectOrder::Building);
		Tower_R->SetActorLocation(UContentsConstValue::InitLocation + float4{ 900.0f, 54.0f, 100.0f });
		Tower_R->SetIsUpgradable(false);

		OuterWall_L = GetWorld()->SpawnActor<AWall>("OuterWall_L", EObjectOrder::Building);
		OuterWall_L->SetActorLocation(UContentsConstValue::InitLocation + float4{ -1000.0f, 36.0f, 100.0f });
		OuterWall_L->SetDir(EEngineDir::Left);
		OuterWall_L->SetIsUpgradable(false);

		OuterWall_R = GetWorld()->SpawnActor<AWall>("OuterWall_R", EObjectOrder::Building);
		OuterWall_R->SetActorLocation(UContentsConstValue::InitLocation + float4{ 1000.0f, 36.0f, 100.0f });
		OuterWall_R->SetIsUpgradable(false);

		BowVendor = GetWorld()->SpawnActor<ABowVendor>("BowVendor", EObjectOrder::Building);
		BowVendor->SetActorLocation(UContentsConstValue::InitLocation + float4{ 150.0f, 52.0f, 100.0f });
		BowVendor->SetActive(false);

		HammerVendor = GetWorld()->SpawnActor<AHammerVendor>("HammerVendor", EObjectOrder::Building);
		HammerVendor->SetActorLocation(UContentsConstValue::InitLocation + float4{ -150.0f, 52.0f, 100.0f });
		HammerVendor->SetActive(false);
	}
}

void ATownCenter::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	CheckIsUpdatable();
	
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
		{
			CurTier = ESpotUpgrade::Tier1;
			Renderer_Campfire->SetSprite("Campfire_01.png");
			RequiredCoin = 3;
		}
		{
			BowVendor->SetActive(true);
			HammerVendor->SetActive(true);
			InnerWall_L->SetIsUpgradable(true);
			InnerWall_R->SetIsUpgradable(true);
		}
		break;
	}
	case ESpotUpgrade::Tier1:
	{
		{
			CurTier = ESpotUpgrade::Tier2;
			Renderer_Campfire->SetSprite("Campfire_02.png");
			Renderer_Banner->SetActive(true);
			Renderer_Castle->SetSprite("TownCenter_02.png");
			RequiredCoin = 6;
			SkipUpgradeProgress = false;
		}
		{
			Tower_L->SetIsUpgradable(true);
			Tower_R->SetIsUpgradable(true);
		}
		break;
	}
	case ESpotUpgrade::Tier2:
	{
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
		}
		{
			OuterWall_L->SetIsUpgradable(true);
			OuterWall_R->SetIsUpgradable(true);
			Tower_L->SetIsUpgradable(true);
			Tower_R->SetIsUpgradable(true);
			InnerWall_L->SetIsUpgradable(true);
			InnerWall_R->SetIsUpgradable(true);
		}
		break;
	}
	case ESpotUpgrade::Tier3:
	{
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
		}
		{
			OuterWall_L->SetIsUpgradable(true);
			OuterWall_R->SetIsUpgradable(true);
			Tower_L->SetIsUpgradable(true);
			Tower_R->SetIsUpgradable(true);
			InnerWall_L->SetIsUpgradable(true);
			InnerWall_R->SetIsUpgradable(true);
		}
		break;
	}
	default:
		break;
	}
}

void ATownCenter::CheckIsUpdatable()
{
	switch (CurTier)
	{
	case ESpotUpgrade::Tier1:
	{
		if (InnerWall_L->GetCurTier() == ESpotUpgrade::Tier1)
		{
			InnerWall_L->SetIsUpgradable(false);
		}
		if (InnerWall_R->GetCurTier() == ESpotUpgrade::Tier1)
		{
			InnerWall_R->SetIsUpgradable(false);
		}
		break;
	}
	case ESpotUpgrade::Tier2:
	{
		if (Tower_L->GetCurTier() == ESpotUpgrade::Tier1)
		{
			Tower_L->SetIsUpgradable(false);
		}
		if (Tower_R->GetCurTier() == ESpotUpgrade::Tier1)
		{
			Tower_R->SetIsUpgradable(false);
		}
		break;
	}
	case ESpotUpgrade::Tier3:
	{
		if (OuterWall_L->GetCurTier() == ESpotUpgrade::Tier1)
		{
			OuterWall_L->SetIsUpgradable(false);
		}
		if (OuterWall_R->GetCurTier() == ESpotUpgrade::Tier1)
		{
			OuterWall_R->SetIsUpgradable(false);
		}
		if (Tower_L->GetCurTier() == ESpotUpgrade::Tier2)
		{
			Tower_L->SetIsUpgradable(false);
		}
		if (Tower_R->GetCurTier() == ESpotUpgrade::Tier2)
		{
			Tower_R->SetIsUpgradable(false);
		}
		if (InnerWall_L->GetCurTier() == ESpotUpgrade::Tier2)
		{
			InnerWall_L->SetIsUpgradable(false);
		}
		if (InnerWall_R->GetCurTier() == ESpotUpgrade::Tier2)
		{
			InnerWall_R->SetIsUpgradable(false);
		}
		break;
	}
	case ESpotUpgrade::Tier4:
	{
		if (OuterWall_L->GetCurTier() == ESpotUpgrade::Tier3)
		{
			OuterWall_L->SetIsUpgradable(false);
		}
		if (OuterWall_R->GetCurTier() == ESpotUpgrade::Tier3)
		{
			OuterWall_R->SetIsUpgradable(false);
		}
		if (Tower_L->GetCurTier() == ESpotUpgrade::Tier3)
		{
			Tower_L->SetIsUpgradable(false);
		}
		if (Tower_R->GetCurTier() == ESpotUpgrade::Tier3)
		{
			Tower_R->SetIsUpgradable(false);
		}
		if (InnerWall_L->GetCurTier() == ESpotUpgrade::Tier3)
		{
			InnerWall_L->SetIsUpgradable(false);
		}
		if (InnerWall_R->GetCurTier() == ESpotUpgrade::Tier3)
		{
			InnerWall_R->SetIsUpgradable(false);
		}
		break;
	}
	default:
		break;
	}
}

void ATownCenter::ActiveStart()
{
	Super::ActiveStart();

	/*
	Renderer_Campfire->SetPlusColor({ 0.1f, 0.1f, 0.0f, 1.0f });
	Renderer_Banner->SetPlusColor({ 0.1f, 0.1f, 0.0f, 1.0f });
	Renderer_Castle->SetPlusColor({ 0.1f, 0.1f, 0.0f, 1.0f });

	for (int i = 0; i < 4; i++)
	{
		Renderer_Walls[i]->SetPlusColor({ 0.1f, 0.1f, 0.0f, 1.0f });
	}
	*/
}

void ATownCenter::ActiveEnd()
{
	Super::ActiveEnd();

	/*
	Renderer_Campfire->SetPlusColor({ 0.0f, 0.0f, 0.0f, 0.0f });
	Renderer_Banner->SetPlusColor({ 0.0f, 0.0f, 0.0f, 0.0f });
	Renderer_Castle->SetPlusColor({ 0.0f, 0.0f, 0.0f, 0.0f });

	for (int i = 0; i < 4; i++)
	{
		Renderer_Walls[i]->SetPlusColor({ 0.0f, 0.0f, 0.0f, 0.0f });
	}
	*/
}
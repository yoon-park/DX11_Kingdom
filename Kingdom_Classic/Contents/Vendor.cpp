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

		Renderer_Sign = CreateDefaultSubObject<USpriteRenderer>("Renderer_Vendor");
		Renderer_Sign->SetupAttachment(Root);

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

	for (int i = 0; i < 3; i++)
	{
		std::shared_ptr<ATool> Tool = GetWorld()->SpawnActor<ATool>("Tool", EObjectOrder::Other);
		USpriteRenderer* Renderer_Tool = Tool->GetRenderer();
		FVector VendorLocation;

		float4 ImageScale = UContentsConstValue::MapTexScale;
		float4 InitLocation = { ImageScale.hX(), -ImageScale.hY(), 0.0f };

		switch (Type)
		{
		case EBuildingObjectType::BowVendor:
		{
			VendorLocation = InitLocation + float4{ 150.0f, 52.0f, 100.0f };
			Tool->SetActorLocation(VendorLocation + float4{ 16.0f + 6.0f * i, -21.0f, 0.0f, 0.0f });
			Renderer_Tool->SetSprite("Bow.png");
			Renderer_Tool->SetAutoSize(1.0f, true);
			Renderer_Tool->SetOrder(ERenderOrder::BuildingFront);
			break;
		}
		case EBuildingObjectType::HammerVendor:
		{
			VendorLocation = InitLocation + float4{ -150.0f, 52.0f, 100.0f };
			Tool->SetActorLocation(VendorLocation + float4{ -38.0f + 7.0f * i, -24.0f, 0.0f, 0.0f });
			Renderer_Tool->SetSprite("Hammer.png");
			Renderer_Tool->SetAutoSize(1.0f, true);
			Renderer_Tool->SetOrder(ERenderOrder::BuildingFront);
			break;
		}
		default:
			break;
		}

		Tools.push_back(Tool.get());
	}

	SetCoinIndicatorLocation();
	StateInit();
}

void AVendor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);

	SetDir(_DeltaTime);
	CheckIsBuyable();
}

void AVendor::SetDir(float _DeltaTime)
{
	if (Timer_Dir <= 0.0f)
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

		Timer_Dir = 2.0f;
	}
	else
	{
		Timer_Dir -= _DeltaTime;
	}
}

void AVendor::CheckIsBuyable()
{
	if (State.GetCurStateName() == "Buy")
	{
		IsBuyable = false;
	}
	else if (LeftSlot == 0)
	{
		IsBuyable = false;
	}
	else
	{
		IsBuyable = true;
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
		State.SetEndFunction("Active", std::bind(&AVendor::ActiveEnd, this));

		State.CreateState("Buy");
		State.SetStartFunction("Buy", std::bind(&AVendor::BuyStart, this));
		State.SetUpdateFunction("Buy", std::bind(&AVendor::Buy, this, std::placeholders::_1));
		State.SetEndFunction("Buy", std::bind(&AVendor::BuyEnd, this));
	}

	State.ChangeState("Inactive");
}

void AVendor::InactiveStart()
{
	SetCoinIndicatorActive(false, 3);
}

void AVendor::ActiveStart()
{
	SetCoinIndicatorActive(true, RequiredCoin);
	Renderer_Sign->SetActive(true);
}

void AVendor::BuyStart()
{
	Tools[3 - LeftSlot]->State.ChangeState("Create");
}

void AVendor::Inactive(float _DeltaTime)
{
	if (IsPlayerContact == true && IsBuyable == true)
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

	if (LeftCoin == 0 && LeftSlot != 0)
	{
		State.ChangeState("Buy");
		return;
	}

	CheckPlayer();
	CheckLeftCoin();
}

void AVendor::Buy(float _DeltaTime)
{
	State.ChangeState("InActive");
	return;
}

void AVendor::ActiveEnd()
{
	Renderer_Sign->SetActive(false);
}

void AVendor::BuyEnd()
{
	LeftSlot -= 1;
	LeftCoin = RequiredCoin;
}
#include "PreCompile.h"
#include "HammerVendor.h"

AHammerVendor::AHammerVendor()
{
	Type = EBuildingObjectType::HammerVendor;
	RequiredCoin = 3;
}

AHammerVendor::~AHammerVendor()
{

}

void AHammerVendor::BeginPlay()
{
	Super::BeginPlay();

	{
		Renderer_NPC->SetAutoSize(1.0f, true);
		Renderer_NPC->SetPosition({ 0.0f, -13.0f, 0.0f, 0.0f });
		Renderer_NPC->SetOrder(ERenderOrder::BackObject);

		Renderer_Vendor->SetSprite("HammerVendor.png");
		Renderer_Vendor->SetAutoSize(1.0f, true);
		Renderer_Vendor->SetOrder(ERenderOrder::Building);
	}
	{
		Renderer_NPC->CreateAnimation("Idle", "Merchant_Walk.png", 0.8f, true, 0, 5);
		Renderer_NPC->ChangeAnimation("Idle");
	}
}

void AHammerVendor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AHammerVendor::SetCoinIndicatorLocation()
{
	Renderer_Coins[0]->SetPosition({ -50.0f, 25.0f, 0.0f, 0.0f });
	Renderer_Coins[1]->SetPosition({ -35.0f, 25.0f, 0.0f, 0.0f });
	Renderer_Coins[2]->SetPosition({ -20.0f, 25.0f, 0.0f, 0.0f });
}
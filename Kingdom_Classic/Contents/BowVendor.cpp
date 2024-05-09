#include "PreCompile.h"
#include "BowVendor.h"

ABowVendor::ABowVendor()
{
	Type = EBuildingObjectType::BowVendor;
	RequiredCoin = 2;
}

ABowVendor::~ABowVendor()
{

}

void ABowVendor::BeginPlay()
{
	Super::BeginPlay();

	{
		Renderer_NPC->SetAutoSize(1.0f, true);
		Renderer_NPC->SetPosition({ 0.0f, -13.0f, 0.0f, 0.0f });
		Renderer_NPC->SetOrder(ERenderOrder::BackObject);

		Renderer_Vendor->SetSprite("BowVendor.png");
		Renderer_Vendor->SetAutoSize(1.0f, true);
		Renderer_Vendor->SetOrder(ERenderOrder::Building);
	}
	{
		Renderer_NPC->CreateAnimation("Idle", "Merchant_Walk.png", 0.8f, true, 0, 5);
		Renderer_NPC->ChangeAnimation("Idle");
	}
}

void ABowVendor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ABowVendor::SetCoinIndicatorLocation()
{
	Renderer_Coins[0]->SetPosition({ 10.0f, 25.0f, 0.0f, 0.0f });
	Renderer_Coins[1]->SetPosition({ 25.0f, 25.0f, 0.0f, 0.0f });
}
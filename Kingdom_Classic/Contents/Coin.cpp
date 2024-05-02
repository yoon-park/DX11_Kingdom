#include "PreCompile.h"
#include "Coin.h"

#include "PlayGameMode.h"
#include "Player.h"

ACoin::ACoin()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetScale(FVector(10.0f, 10.0f, 100.0f));
	Collision->SetCollisionGroup(ECollisionOrder::Coin);
	Collision->SetCollisionType(ECollisionType::Rect);

	SetRoot(Root);
}

ACoin::~ACoin()
{

}

void ACoin::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderOrder::GroundObject);

	Renderer->CreateAnimation("Stop", "Coin_Pay", 0.10f);
	Renderer->CreateAnimation("Spin", "Coin_Spin", 0.10f);

	StateInit();
}

void ACoin::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	CheckGround();
	State.Update(_DeltaTime);
}

void ACoin::CheckGround()
{
	Super::CheckGround();

	std::shared_ptr<UEngineTexture> Tex = UContentsConstValue::MapTex;

#ifdef _DEBUG
	if (Tex == nullptr)
	{
		MsgBoxAssert("픽셀충돌을 체크할 맵 이미지가 존재하지 않습니다.");
	}
#endif

	float4 Pos = GetActorLocation();
	Pos.Y = -Pos.Y + 5.0f;

	Color8Bit Color = Tex->GetColor(Pos, Color8Bit::Blue);
	if (Color == Color8Bit::Black)
	{
		IsGround = true;
		CurGroundType = EGroundType::Plain;
		return;
	}
	else
	{
		IsGround = false;
		CurGroundType = EGroundType::None;
		return;
	}
}

void ACoin::CheckAbsorb()
{
	Collision->CollisionEnter(ECollisionOrder::NPC, [=](std::shared_ptr<UCollision> _Collision)
		{
			AbsorbOwner = dynamic_cast<AMovingActor*>(_Collision->GetActor());
			return;
		}
	);

	Collision->CollisionEnter(ECollisionOrder::Horse, [=](std::shared_ptr<UCollision> _Collision)
		{
			AbsorbOwner = dynamic_cast<AMovingActor*>(_Collision->GetActor());
			return;
		}
	);

	Collision->CollisionEnter(ECollisionOrder::Monster, [=](std::shared_ptr<UCollision> _Collision)
		{
			AbsorbOwner = dynamic_cast<AMovingActor*>(_Collision->GetActor());
			return;
		}
	);
}

void ACoin::StateInit()
{
	{
		State.CreateState("Idle");
		State.SetStartFunction("Idle", std::bind(&ACoin::IdleStart, this));
		State.SetUpdateFunction("Idle", std::bind(&ACoin::Idle, this, std::placeholders::_1));

		State.CreateState("PaySpot");
		State.SetStartFunction("PaySpot", std::bind(&ACoin::PaySpotStart, this));
		State.SetUpdateFunction("PaySpot", std::bind(&ACoin::PaySpot, this, std::placeholders::_1));

		State.CreateState("PayGround");
		State.SetStartFunction("PayGround", std::bind(&ACoin::PayGroundStart, this));
		State.SetUpdateFunction("PayGround", std::bind(&ACoin::PayGround, this, std::placeholders::_1));

		State.CreateState("Wait");
		State.SetUpdateFunction("Wait", std::bind(&ACoin::Wait, this, std::placeholders::_1));

		State.CreateState("Fall");
		State.SetStartFunction("Fall", std::bind(&ACoin::FallStart, this));
		State.SetUpdateFunction("Fall", std::bind(&ACoin::Fall, this, std::placeholders::_1));

		State.CreateState("Disappear");
		State.SetUpdateFunction("Disappear", std::bind(&ACoin::Disappear, this, std::placeholders::_1));

		State.CreateState("Absorb");
		State.SetUpdateFunction("Absorb", std::bind(&ACoin::Absorb, this, std::placeholders::_1));
	}

	ASpot* CurSpot = APlayGameMode::MainPlayer->GetCurSpot();

	if (CurSpot == nullptr)
	{
		State.ChangeState("PayGround");
	}
	else
	{
		if (CurSpot->GetIsUpgradable() == true)
		{
			State.ChangeState("PaySpot");
		}
		else
		{
			State.ChangeState("PayGround");
		}
	}
}

void ACoin::IdleStart()
{
	Renderer->ChangeAnimation("Spin");
}

void ACoin::PaySpotStart()
{
	Renderer->ChangeAnimation("Stop");
	Speed = 150.0f;
}

void ACoin::PayGroundStart()
{
	Renderer->ChangeAnimation("Spin");
	Speed = 150.0f;
}

void ACoin::FallStart()
{
	Renderer->ChangeAnimation("Stop");
}

void ACoin::Idle(float _DeltaTime)
{
	if (AbsorbOwner != nullptr)
	{
		State.ChangeState("Absorb");
		return;
	}

	CheckAbsorb();
}

void ACoin::PaySpot(float _DeltaTime)
{
	if (APlayGameMode::MainPlayer->GetIsPaying() == false)
	{
		State.ChangeState("Fall");
		return;
	}

	FVector Indicator_Location = APlayGameMode::MainPlayer->GetCurSpot()->GetCoinLocation(APlayGameMode::MainPlayer->GetCurCoinIndex());
	FVector Coin_Location = GetActorLocation();

	FVector Diff = Indicator_Location - Coin_Location;

	if (Diff.Size3D() <= 0.05)
	{
		State.ChangeState("Wait");
		return;
	}

	FVector Dir = Diff.Normalize3DReturn();

	AddActorLocation(Dir * _DeltaTime * Speed);
}

void ACoin::PayGround(float _DeltaTime)
{
	if (IsGround == true)
	{
		State.ChangeState("Idle");
		return;
	}

	AddActorLocation(FVector::Down * _DeltaTime * Speed);
}

void ACoin::Wait(float _DeltaTime)
{
	if (APlayGameMode::MainPlayer->GetCurSpot()->GetLeftCoin() == 0)
	{
		State.ChangeState("Disappear");
		return;
	}

	if (APlayGameMode::MainPlayer->GetIsPaying() == false)
	{
		State.ChangeState("Fall");
		return;
	}
}

void ACoin::Fall(float _DeltaTime)
{
	if (IsGround == true)
	{
		State.ChangeState("Idle");
		return;
	}

	AddActorLocation(FVector::Down * _DeltaTime * Speed);
}

void ACoin::Disappear(float _DeltaTime)
{
	if (Alpha < 0.0f)
	{
		Destroy();
		return;
	}

	Alpha -= _DeltaTime * 5;
	Renderer->SetMulColor(float4(1.0f, 1.0f, 1.0f, Alpha));
}

void ACoin::Absorb(float _DeltaTime)
{
	FVector Coin_Location = GetActorLocation();
	FVector Owner_Location = AbsorbOwner->GetActorLocation();
	Owner_Location.Y += 20.0f;

	FVector Diff = Owner_Location - Coin_Location;

	if (Diff.Size3D() <= 0.1f)
	{
		Destroy();
		return;
	}

	FVector Dir = Diff.Normalize3DReturn();

	AddActorLocation(Dir * _DeltaTime * Speed);
}
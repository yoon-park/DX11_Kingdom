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
	MoveUpdate(_DeltaTime);
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
	if (
		Color == Color8Bit(0, 255, 255, 255) ||
		Color == Color8Bit(255, 0, 255, 255)
		)
	{
		IsGround = true;
		CurGroundType = EGroundType::Plain;
		return;
	}
	else if (Color == Color8Bit::Black)
	{
		IsGround = true;
		CurGroundType = EGroundType::Forest;
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

void ACoin::CalMoveVector(float _DeltaTime)
{

}

void ACoin::CalJumpVector(float _DeltaTime)
{

}

void ACoin::CalGravityVector(float _DeltaTime)
{
	if (
		IsGround == true ||
		State.GetCurStateName() == "PaySpot" ||
		State.GetCurStateName() == "Wait" ||
		State.GetCurStateName() == "Disappear" ||
		State.GetCurStateName() == "Absorb"
		)
	{
		SetGravityVector(FVector::Zero);
		return;
	}

	GravityVector += FVector::Down * GravityAcc * _DeltaTime;
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
		State.SetStartFunction("Wait", std::bind(&ACoin::WaitStart, this));
		State.SetUpdateFunction("Wait", std::bind(&ACoin::Wait, this, std::placeholders::_1));

		State.CreateState("Fall");
		State.SetStartFunction("Fall", std::bind(&ACoin::FallStart, this));
		State.SetUpdateFunction("Fall", std::bind(&ACoin::Fall, this, std::placeholders::_1));

		State.CreateState("Disappear");
		State.SetUpdateFunction("Disappear", std::bind(&ACoin::Disappear, this, std::placeholders::_1));

		State.CreateState("Absorb");
		State.SetStartFunction("Absorb", std::bind(&ACoin::AbsorbStart, this));
		State.SetUpdateFunction("Absorb", std::bind(&ACoin::Absorb, this, std::placeholders::_1));
	}
	{
		Speed = 0.0f;
		MoveVector = FVector::Zero;
		MoveAcc = 1000.0f;
		JumpVector = FVector::Zero;
		GravityVector = FVector::Zero;
		GravityAcc = 500.0f;
		LastMoveVector = FVector::Zero;
	}

	ABuildingObject* CurBuilding = APlayGameMode::MainPlayer->GetCurBuilding();

	if (CurBuilding == nullptr)
	{
		State.ChangeState("PayGround");
	}
	else
	{
		if (CurBuilding->State.GetCurStateName() == "Active")
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

	SetMoveVector(FVector::Zero);
}

void ACoin::PaySpotStart()
{
	Renderer->ChangeAnimation("Stop");

	Speed = 150.0f;
	SetMoveVector(FVector::Zero);
}

void ACoin::PayGroundStart()
{
	Renderer->ChangeAnimation("Spin");

	SetMoveVector(FVector::Zero);
}

void ACoin::WaitStart()
{
	Renderer->ChangeAnimation("Stop");

	SetMoveVector(FVector::Zero);
}

void ACoin::FallStart()
{
	Renderer->ChangeAnimation("Stop");

	SetMoveVector(FVector::Zero);
}

void ACoin::AbsorbStart()
{
	Renderer->ChangeAnimation("Stop");

	Speed = 150.0f;
	SetMoveVector(FVector::Zero);
}

void ACoin::Idle(float _DeltaTime)
{
	CheckAbsorb();

	if (AbsorbOwner != nullptr)
	{
		State.ChangeState("Absorb");
		return;
	}
}

void ACoin::PaySpot(float _DeltaTime)
{
	if (APlayGameMode::MainPlayer->GetIsPaying() == false)
	{
		State.ChangeState("Fall");
		return;
	}

	FVector Indicator_Location = APlayGameMode::MainPlayer->GetCurBuilding()->GetCoinLocation(APlayGameMode::MainPlayer->GetCurCoinIndex());
	FVector Coin_Location = GetActorLocation();

	FVector Diff = Indicator_Location - Coin_Location;

	if (Diff.Size3D() <= 0.05)
	{
		State.ChangeState("Wait");
		return;
	}

	FVector Dir = Diff.Normalize3DReturn();

	SetMoveVector(Dir * Speed);
}

void ACoin::PayGround(float _DeltaTime)
{
	if (IsGround == true)
	{
		State.ChangeState("Idle");
		return;
	}
}

void ACoin::Wait(float _DeltaTime)
{
	if (APlayGameMode::MainPlayer->GetCurBuilding()->GetLeftCoin() == 0)
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

	if (Diff.Size3D() <= 4.0f)
	{
		Destroy();
		return;
	}

	FVector Dir = Diff.Normalize3DReturn();

	SetMoveVector(Dir * Speed);
}
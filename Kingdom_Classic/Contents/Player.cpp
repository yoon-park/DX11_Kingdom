#include "PreCompile.h"
#include "Player.h"

#include "PlayGameMode.h"
#include "ContentsTime.h"

APlayer::APlayer()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	
	Renderer_Player = CreateDefaultSubObject<USpriteRenderer>("Renderer_Player");
	Renderer_Player->SetupAttachment(Root);
	Renderer_Player->SetPivot(EPivot::BOT);

	Renderer_Horse = CreateDefaultSubObject<USpriteRenderer>("Renderer_Horse");
	Renderer_Horse->SetupAttachment(Root);
	Renderer_Horse->SetPivot(EPivot::BOT);

	Collision_Player = CreateDefaultSubObject<UCollision>("Collision_Player");
	Collision_Player->SetupAttachment(Root);
	Collision_Player->SetScale(FVector(12.0f, 27.0f, 100.0f));
	Collision_Player->SetPosition(FVector(0.0f, 27.0f, 0.0f));
	Collision_Player->SetCollisionGroup(ECollisionOrder::Player);
	Collision_Player->SetCollisionType(ECollisionType::Rect);

	Collision_Horse_Front = CreateDefaultSubObject<UCollision>("Collision_Horse_Front");
	Collision_Horse_Front->SetupAttachment(Root);
	Collision_Horse_Front->SetScale(FVector(15.0f, 30.0f, 100.0f));
	Collision_Horse_Front->SetPosition(FVector(13.0f, 15.0f, 0.0f));
	Collision_Horse_Front->SetCollisionGroup(ECollisionOrder::Horse);
	Collision_Horse_Front->SetCollisionType(ECollisionType::Rect);

	SetRoot(Root);
	
	InputOn();
}

APlayer::~APlayer()
{

}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	{
		Renderer_Player->SetAutoSize(1.0f, true);
		Renderer_Player->SetOrder(ERenderOrder::Player);

		Renderer_Horse->SetAutoSize(1.0f, true);
		Renderer_Horse->SetOrder(ERenderOrder::Player);
	}
	{
		Renderer_Player->CreateAnimation("Idle", "Player_Idle.png", 0.13f, true, 0, 15);
		Renderer_Player->CreateAnimation("Walk", "Player_Walk.png", 0.10f, true, 0, 7);
		Renderer_Player->CreateAnimation("Run", "Player_Run.png", 0.05f, true, 0, 11);
		Renderer_Player->CreateAnimation("Rear", "Player_Rear.png", 0.10f, false, 0, 12);
		Renderer_Player->CreateAnimation("Eat", "Player_Eat.png", 0.10f, false, 0, 13);

		Renderer_Horse->CreateAnimation("Idle", "Player_Horse_Idle.png", 0.13f, true, 0, 15);
		Renderer_Horse->CreateAnimation("Walk", "Player_Horse_Walk.png", 0.10f, true, 0, 7);
		Renderer_Horse->CreateAnimation("Run", "Player_Horse_Run.png", 0.05f, true, 0, 11);
		Renderer_Horse->CreateAnimation("Rear", "Player_Horse_Rear.png", 0.10f, false, 0, 12);
		Renderer_Horse->CreateAnimation("Eat", "Player_Horse_Eat.png", 0.10f, false, 0, 13);
	}
	
	StateInit();
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	
	CheckGround();
	CheckSpot();

	State.Update(_DeltaTime);
	MoveUpdate(_DeltaTime);

	DebugMessageFunction(_DeltaTime);
}

void APlayer::ChangeDir(EEngineDir _Dir)
{
	Super::ChangeDir(_Dir);

	if (_Dir == CurDir)
	{
		return;
	}
	else
	{
		PrevDir = CurDir;
		CurDir = _Dir;

		switch (CurDir)
		{
		case EEngineDir::Left:
			Renderer_Player->SetDir(EEngineDir::Left);
			Renderer_Horse->SetDir(EEngineDir::Left);
			Collision_Horse_Front->SetPosition(FVector(-13.0f, 15.0f, 0.0f));
			break;
		case EEngineDir::Right:
			Renderer_Player->SetDir(EEngineDir::Right);
			Renderer_Horse->SetDir(EEngineDir::Right);
			Collision_Horse_Front->SetPosition(FVector(13.0f, 15.0f, 0.0f));
			break;
		case EEngineDir::MAX:
			break;
		default:
			break;
		}
	}
}

void APlayer::CheckGround()
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
	Pos += {0.0f, 25.0f, 0.0f};

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

void APlayer::CheckSpot()
{
	Collision_Horse_Front->CollisionStay(ECollisionOrder::Spot, [=](std::shared_ptr<UCollision> _Collision)
		{
			CurSpot = dynamic_cast<ASpot*>(_Collision->GetActor());
			return;
		}
	);

	Collision_Horse_Front->CollisionExit(ECollisionOrder::Spot, [=](std::shared_ptr<UCollision> _Collision)
		{
			CurSpot = nullptr;
			return;
		}
	);
}

void APlayer::CreateCoin()
{
	std::shared_ptr<ACoin> Coin = GetWorld()->SpawnActor<ACoin>("Coin", EObjectOrder::Coin);
	Coin->SetActorLocation(GetActorLocation() + float4(0.0f, 30.0f, 0.0f));
	CurCoin = Coin.get();
	CurCoinIndex += 1;
}

void APlayer::DebugMessageFunction(float _Delta)
{
	{
		std::string Msg = std::format("PlayerPos : {}\n", GetActorLocation().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
	{
		std::string Msg = std::format("MousePos : {}\n", GEngine->EngineWindow.GetScreenMousePos().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
	{
		std::string Msg = std::format("Frame : {}\n", 1.0f / _Delta);
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
	{
		std::string Msg = std::format("CurTime : {}\n", APlayGameMode::ContentsTimer->GetCount());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
	{
		std::string Msg = std::format("Date : {}\n", APlayGameMode::ContentsTimer->GetDate());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
	{
		std::string Msg = std::format("IsDay : {}\n", APlayGameMode::ContentsTimer->GetIsDay());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}
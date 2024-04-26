#include "PreCompile.h"
#include "Player.h"

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
	Collision_Player->AddPosition(FVector(0.0f, 27.0f, 0.0f));
	Collision_Player->SetCollisionGroup(ECollisionOrder::Player);
	Collision_Player->SetCollisionType(ECollisionType::Rect);

	Collision_Horse_Front = CreateDefaultSubObject<UCollision>("Collision_Horse_Front");
	Collision_Horse_Front->SetupAttachment(Root);
	Collision_Horse_Front->SetScale(FVector(15.0f, 30.0f, 100.0f));
	Collision_Horse_Front->AddPosition(FVector(13.0f, 15.0f, 0.0f));
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

	State.Update(_DeltaTime);

	DebugMessageFunction();
}

void APlayer::ChangeDir(EEngineDir _Dir)
{
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
			Collision_Horse_Front->AddPosition(FVector(-26.0f, 0.0f, 0.0f));
			break;
		case EEngineDir::Right:
			Renderer_Player->SetDir(EEngineDir::Right);
			Renderer_Horse->SetDir(EEngineDir::Right);
			Collision_Horse_Front->AddPosition(FVector(26.0f, 0.0f, 0.0f));
			break;
		case EEngineDir::MAX:
			break;
		default:
			break;
		}
	}
}

void APlayer::DebugMessageFunction()
{
	{
		std::string Msg = std::format("PlayerPos : {}\n", GetActorLocation().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
	{
		std::string Msg = std::format("MousePos : {}\n", GEngine->EngineWindow.GetScreenMousePos().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}
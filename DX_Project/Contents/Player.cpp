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

	SpotNearbyCheck = CreateDefaultSubObject<UCollision>("SpotNearbyCheck");
	SpotNearbyCheck->SetupAttachment(Root);
	SpotNearbyCheck->SetScale(FVector(100.0f, 300.0f, 100.0f));
	SpotNearbyCheck->SetCollisionGroup(ECollisionOrder::Player);
	SpotNearbyCheck->SetCollisionType(ECollisionType::Rect);

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
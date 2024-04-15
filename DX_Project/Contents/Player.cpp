#include "PreCompile.h"
#include "Player.h"

APlayer::APlayer()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetScale(FVector(100.0f, 100.0f, 100.0f));
	Renderer->SetupAttachment(Root);

	USpriteRenderer* ChildRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	ChildRenderer->SetupAttachment(Root);
	ChildRenderer->SetScale(FVector(100.0f, 100.0f, 100.0f));
	ChildRenderer->AddPosition({ -200.0f, 0.0f, 0.0f });

	//Collision = CreateDefaultSubObject<UCollision>("Collision");
	//Collision->SetupAttachment(Renderer);

	SetRoot(Root);
	
	InputOn();
}

APlayer::~APlayer()
{

}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(100.0f, 100.0f, 100.0f));
	
	/*
	Renderer->CreateAnimation("Die", "Die");
	Renderer->CreateAnimation("Idle", "Idle");
	Renderer->CreateAnimation("Jump", "Jump");
	Renderer->CreateAnimation("Run", "Run", 0.1f);
	*/
	
	StateInit();

	/*
	Renderer->SetAutoSize(10.0f, true);
	Renderer->SetOrder(ERenderOrder::Player);
	*/
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
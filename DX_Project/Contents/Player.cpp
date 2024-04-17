#include "PreCompile.h"
#include "Player.h"

APlayer::APlayer()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetPivot(EPivot::BOT);

	SetRoot(Root);
	
	InputOn();
}

APlayer::~APlayer()
{

}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("deer_eat_1.png");
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderOrder::Player);
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	DebugMessageFunction();

	float Speed = 500.0f;

	if (IsPress('A') == true)
	{
		AddActorLocation(FVector::Left * _DeltaTime * Speed);
	}

	if (IsPress('D') == true)
	{
		AddActorLocation(FVector::Right * _DeltaTime * Speed);
	}

	/*
	if (IsPress('W') == true)
	{
		AddActorLocation(FVector::Up * _DeltaTime * Speed);
	}

	if (IsPress('S') == true)
	{
		AddActorLocation(FVector::Down * _DeltaTime * Speed);
	}
	*/
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
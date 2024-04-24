#include "PreCompile.h"
#include "Coin.h"

ACoin::ACoin()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetPivot(EPivot::BOT);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetScale(FVector(500.0f, 800.0f, 100.0f));
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
	Renderer->SetOrder(ERenderOrder::UI);

	Renderer->CreateAnimation("Pay", "Coin_Pay", 0.10f);
	Renderer->CreateAnimation("Spin", "Coin_Spin", 0.10f);

	StateInit();
}

void ACoin::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void ACoin::StateInit()
{
	{
		State.CreateState("Idle");
		State.SetStartFunction("Idle", std::bind(&ACoin::IdleStart, this));
		State.SetUpdateFunction("Idle", std::bind(&ACoin::Idle, this, std::placeholders::_1));

		State.CreateState("Fall");
		State.SetStartFunction("Fall", std::bind(&ACoin::FallStart, this));
		State.SetUpdateFunction("Fall", std::bind(&ACoin::Fall, this, std::placeholders::_1));

		State.CreateState("Pay");
		State.SetStartFunction("Pay", std::bind(&ACoin::PayStart, this));
		State.SetUpdateFunction("Pay", std::bind(&ACoin::Pay, this, std::placeholders::_1));
	}

	State.ChangeState("Idle");
}

void ACoin::IdleStart()
{
	Renderer->ChangeAnimation("Spin");
}

void ACoin::FallStart()
{
	Renderer->ChangeAnimation("Spin");

	Speed = 150.0f;
}

void ACoin::PayStart()
{
	Renderer->ChangeAnimation("Pay");

	Speed = 50.0f;
}

void ACoin::Idle(float _DeltaTime)
{

}

void ACoin::Fall (float _DeltaTime)
{

}

void ACoin::Pay(float _DeltaTime)
{

}
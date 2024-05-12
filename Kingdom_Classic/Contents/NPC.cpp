#include "PreCompile.h"
#include "NPC.h"

ANPC::ANPC()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetPivot(EPivot::BOT);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetCollisionGroup(ECollisionOrder::NPC);
	Collision->SetCollisionType(ECollisionType::Rect);

	SetRoot(Root);
}

ANPC::~ANPC()
{

}

void ANPC::BeginPlay()
{
	Super::BeginPlay();

	{
		Renderer->SetAutoSize(1.0f, true);
		Renderer->SetOrder(ERenderOrder::MovingActor);
	}
	{
		Renderer->CreateAnimation("Vagrant_Idle", "Vagrant_Idle.png", 0.13f, true, 0, 4);
		Renderer->CreateAnimation("Vagrant_Walk", "Vagrant_Walk.png", 0.13f, true, 0, 5);
		Renderer->CreateAnimation("Vagrant_Run", "Vagrant_Run.png", 0.13f, true, 0, 5);
		Renderer->CreateAnimation("Villager_Idle", "Villager_Idle.png", 0.13f, true, 0, 5);
		Renderer->CreateAnimation("Villager_Walk", "Villager_Walk.png", 0.13f, true, 0, 5);
		Renderer->CreateAnimation("Villager_Run", "Villager_Run.png", 0.13f, true, 0, 5);
		Renderer->CreateAnimation("Villager_Bumped", "Villager_Bumped.png", 0.13f, true, 0, 0);
		Renderer->CreateAnimation("Villager_Getup", "Villager_Getup.png", 0.13f, true, 0, 3);
		Renderer->CreateAnimation("Archer_Idle", "Archer_Idle.png", 0.13f, true, 0, 3);
		Renderer->CreateAnimation("Archer_Walk", "Archer_Walk.png", 0.13f, true, 0, 5);
		Renderer->CreateAnimation("Archer_Run", "Archer_Run.png", 0.13f, true, 0, 5);
		Renderer->CreateAnimation("Archer_Prep", "Archer_Prep.png", 0.13f, true, 0, 1);
		Renderer->CreateAnimation("Archer_Shoot", "Archer_Shoot.png", 0.13f, true, 0, 2);
		Renderer->CreateAnimation("Builder_Idle", "Builder_Idle.png", 0.13f, true, 0, 5);
		Renderer->CreateAnimation("Builder_Walk", "Builder_Walk.png", 0.13f, true, 0, 5);
		Renderer->CreateAnimation("Builder_Run", "Builder_Run.png", 0.13f, true, 0, 5);
		Renderer->CreateAnimation("Builder_Work", "Builder_Work.png", 0.13f, true, 0, 6);
	}

	StateInit();
}

void ANPC::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void ANPC::ChangeDir(EEngineDir _Dir)
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
			Renderer->SetDir(EEngineDir::Left);
			break;
		case EEngineDir::Right:
			Renderer->SetDir(EEngineDir::Right);
			break;
		case EEngineDir::MAX:
			break;
		default:
			break;
		}
	}
}
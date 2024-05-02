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
}

ANPC::~ANPC()
{

}

void ANPC::BeginPlay()
{
	Super::BeginPlay();
}

void ANPC::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
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
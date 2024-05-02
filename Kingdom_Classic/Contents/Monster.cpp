#include "PreCompile.h"
#include "Monster.h"

AMonster::AMonster()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetPivot(EPivot::BOT);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetCollisionGroup(ECollisionOrder::Monster);
	Collision->SetCollisionType(ECollisionType::Rect);
}

AMonster::~AMonster()
{

}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
}

void AMonster::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AMonster::ChangeDir(EEngineDir _Dir)
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
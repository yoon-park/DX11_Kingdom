#include "PreCompile.h"
#include "Tool.h"

ATool::ATool()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);

	SetRoot(Root);
}

ATool::~ATool()
{
	
}

void ATool::BeginPlay()
{
	Super::BeginPlay();

	StateInit();
}

void ATool::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void ATool::StateInit()
{
	{
		State.CreateState("Inactive");
		State.SetStartFunction("Inactive", std::bind(&ATool::InactiveStart, this));
		State.SetUpdateFunction("Inactive", std::bind(&ATool::Inactive, this, std::placeholders::_1));

		State.CreateState("Create");
		State.SetStartFunction("Create", std::bind(&ATool::CreateStart, this));
		State.SetUpdateFunction("Create", std::bind(&ATool::Create, this, std::placeholders::_1));
		State.SetEndFunction("Create", std::bind(&ATool::CreateEnd, this));

		State.CreateState("Active");
		State.SetStartFunction("Active", std::bind(&ATool::ActiveStart, this));
		State.SetUpdateFunction("Active", std::bind(&ATool::Active, this, std::placeholders::_1));
	}

	State.ChangeState("Inactive");
}

void ATool::InactiveStart()
{
	SetActive(false);
}

void ATool::CreateStart()
{
	SetActive(true);
}

void ATool::ActiveStart()
{

}

void ATool::Inactive(float _DeltaTime)
{

}

void ATool::Create(float _DeltaTime)
{
	if (Cnt_Blink == 0)
	{
		State.ChangeState("Active");
		return;
	}

	if (Inter_Blink <= 0)
	{
		if (Cnt_Blink % 2 == 0)
		{
			Renderer->SetPlusColor({ 1.0f, 1.0f, 1.0f, 0.0f });
		}
		else
		{
			Renderer->SetPlusColor({ 0.0f, 0.0f, 0.0f, 0.0f });
		}

		Cnt_Blink -= 1;
		Inter_Blink = 0.1f;
	}
	else
	{
		Inter_Blink -= _DeltaTime;
	}
}

void ATool::Active(float _DeltaTime)
{

}

void ATool::CreateEnd()
{
	Cnt_Blink = 8;
	Inter_Blink = 0.1f;
}
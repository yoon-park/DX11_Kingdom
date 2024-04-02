#include "PreCompile.h"
#include "EngineCore.h"

#include "EngineTexture.h"
#include "Level.h"

UEngineCore* GEngine = nullptr;

UEngineCore::UEngineCore()
{

}

UEngineCore::~UEngineCore()
{
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("Config");

	UEngineFile File = Dir.GetPathFromFile("EngineOption.EData");
	UEngineSerializer Ser;
	EngineOption.Serialize(Ser);

	File.Open(EIOOpenMode::Write, EIODataType::Text);
	File.Save(Ser);
}

void UEngineCore::EngineOptionInit()
{
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("Config");

	if (Dir.IsFile("EngineOption.EData") == false)
	{
		UEngineFile File = Dir.GetPathFromFile("EngineOption.EData");
		UEngineSerializer Ser;
		EngineOption.Serialize(Ser);

		File.Open(EIOOpenMode::Write, EIODataType::Text);
		File.Save(Ser);
	}

	{
		UEngineFile File = Dir.GetPathFromFile("EngineOption.EData");
		UEngineSerializer Ser;
		File = Dir.GetPathFromFile("EngineOption.EData");
		File.Open(EIOOpenMode::Read, EIODataType::Text);
		File.Load(Ser);
		EngineOption.DeSerialize(Ser);
	}
}

void UEngineCore::EngineStart(HINSTANCE _Inst)
{
	LeakCheck;
	GEngine = this;

	EngineOptionInit();
	EngineWindow.Open(EngineOption.WindowTitle);
	EngineWindow.SetWindowScale(EngineOption.WindowScale);
	EngineDevice.Initialize(EngineWindow, EngineOption.ClearColor);

	{
		UserCorePtr->Initialize();
		MainTimer.TimeCheckStart();
	}

	UEngineWindow::WindowMessageLoop(
		std::bind(&UEngineCore::EngineFrameUpdate, this),
		std::bind(&UEngineCore::EngineEnd, this)
	);
}

void UEngineCore::EngineFrameUpdate()
{
	float DeltaTime = MainTimer.TimeCheck();
	UEngineInput::KeyCheckTick(DeltaTime);

	if (NextLevel != nullptr)
	{
		CurLevel = NextLevel;
		NextLevel = nullptr;
	}

	CurLevel->Tick(DeltaTime);
	EngineDevice.RenderStart();
	CurLevel->Render(DeltaTime);
	EngineDevice.RenderEnd();
}

void UEngineCore::EngineEnd()
{
	UEngineSound::ResourcesRelease();
	UEngineTexture::ResourcesRelease();
}

std::shared_ptr<ULevel> UEngineCore::NewLevelCreate(std::string& _Name, std::shared_ptr<AActor> _GameMode)
{
	std::shared_ptr<ULevel> Level = std::make_shared<ULevel>();
	Level->PushActor(_GameMode);
	Level->BeginPlay();
	Levels[_Name] = Level;
	return Level;
}
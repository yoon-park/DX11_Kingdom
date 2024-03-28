#include "PreCompile.h"
#include "EngineCore.h"

#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>

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
	EngineOptionInit();

	EngineWindow.Open(EngineOption.WindowTitle);
	EngineWindow.SetWindowScale(EngineOption.WindowScale);

	{
		UserCorePtr->Initialize();
		MainTimer.TimeCheckStart();
	}

	UEngineWindow::WindowMessageLoop(
		std::bind(&UEngineCore::EngineUpdate, this),
		nullptr
	);
}

void UEngineCore::EngineUpdate()
{
	float DeltaTime = MainTimer.TimeCheck();
	UEngineInput::KeyCheckTick(DeltaTime);
}
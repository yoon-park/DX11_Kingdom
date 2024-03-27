#include "PreCompile.h"
#include "EngineCore.h"

#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include "EngineOption.h"

UEngineCore::UEngineCore()
{

}

UEngineCore::~UEngineCore()
{

}

UEngineCore* GEngine = nullptr;

void UEngineCore::EngineStart(HINSTANCE _Inst)
{
	FEngineOption Option;
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("Config");

	if (Dir.IsFile("EngineOption.EData") == false)
	{
		UEngineFile File = Dir.GetPathFromFile("EngineOption.EData");
		UEngineSerializer Ser;
		Option.Serialize(Ser);

		File.Open(EIOOpenMode::Write, EIODataType::Text);
		File.Save(Ser);
	}

	{
		UEngineFile File = Dir.GetPathFromFile("EngineOption.EData");
		UEngineSerializer Ser;
		File = Dir.GetPathFromFile("EngineOption.EData");
		File.Open(EIOOpenMode::Read, EIODataType::Text);
		File.Load(Ser);
		Option.DeSerialize(Ser);
	}

	EngineWindow.Open(Option.WindowTitle);
	EngineWindow.SetWindowScale(Option.WindowScale);

	UserCorePtr->Initialize();

	UEngineWindow::WindowMessageLoop(
		nullptr,
		nullptr
		//std::bind(&UEngineCore::Update, &Core),
		//std::bind(&UEngineCore::End, &Core)
	);
}
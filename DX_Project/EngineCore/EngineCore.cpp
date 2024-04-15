#include "PreCompile.h"
#include "EngineCore.h"

#include "EngineEditorGUI.h"
#include "EngineDebugMsgWindow.h"

#include "EngineVertexBuffer.h"

#include "GameMode.h"
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

	UEngineEditorGUI::GUIInit();
	UEngineEditorGUI::CreateEditorWindow<UEngineDebugMsgWindow>("DebugMsgWindow");

	{
		UserCorePtr->Initialize();
		MainTimer.TimeCheckStart();
	}

	UEngineWindow::WindowMessageLoop(
		std::bind(&UEngineCore::EngineFrameUpdate, this),
		std::bind(&UEngineCore::EngineEnd, this)
	);

	UEngineEditorGUI::GUIRelease();
}

void UEngineCore::EngineFrameUpdate()
{
	float DeltaTime = MainTimer.TimeCheck();
	UEngineInput::KeyCheckTick(DeltaTime);
	GEngine->EngineWindow.CalculateMouseUpdate(DeltaTime);

	if (NextLevel != nullptr)
	{
		if (CurLevel != nullptr)
		{
			CurLevel->LevelEnd(NextLevel.get());
		}

		NextLevel->LevelStart(CurLevel.get());

		CurLevel = NextLevel;
		NextLevel = nullptr;
	}

	CurLevel->Tick(DeltaTime);

	EngineDevice.RenderStart();
	CurLevel->Render(DeltaTime);
	UEngineEditorGUI::GUIRender(DeltaTime);
	EngineDevice.RenderEnd();

	CurLevel->Destroy();
}

void UEngineCore::EngineEnd()
{
	EngineDevice.EngineResourcesRelease();
}

std::shared_ptr<ULevel> UEngineCore::NewLevelCreate(std::string& _Name, std::shared_ptr<AActor> _GameMode)
{
	std::shared_ptr <AGameMode> GameModePtr = std::dynamic_pointer_cast<AGameMode>(_GameMode);

	if (GameModePtr == nullptr)
	{
		MsgBoxAssert("레벨의 첫 오브젝트가 GameMode를 상속받은 클래스가 아닙니다.");
		return nullptr;
	}

	std::shared_ptr<ULevel> Level = std::make_shared<ULevel>();
	Level->PushActor(_GameMode);
	Levels[_Name] = Level;
	return Level;
}
#include "PreCompile.h"
#include "ContentsCore.h"

#include "TitleGameMode.h"
#include "PlayGameMode.h"

UContentsCore::UContentsCore()
{

}

UContentsCore::~UContentsCore()
{

}

void UContentsCore::Initialize()
{
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
		
		for (UEngineFile& File : Files)
		{
			UEngineSprite::Load(File.GetFullPath());
		}

		std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			std::string Name = Directorys[i].GetFolderName();
			UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
		}

		// UEngineSprite::CreateCutting("CuttingTest.png", 4, 3);
	}

	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Sound");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".wav" });
		
		for (UEngineFile& File : Files)
		{
			UEngineSound::Load(File.GetFullPath());
		}
	}

	GEngine->CreateLevel<ATitleGameMode>("TitleLevel");
	GEngine->CreateLevel<APlayGameMode>("PlayLevel");
	GEngine->ChangeLevel("PlayLevel");
}
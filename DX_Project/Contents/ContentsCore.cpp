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

		{
			UEngineSprite::CreateCutting("Player_Idle.png", 16, 1);
			UEngineSprite::CreateCutting("Player_Walk.png", 16, 1);
			UEngineSprite::CreateCutting("Player_Run.png", 16, 1);
			UEngineSprite::CreateCutting("Player_Rear.png", 16, 1);
			UEngineSprite::CreateCutting("Player_Eat.png", 16, 1);
			UEngineSprite::CreateCutting("Player_Horse_Idle.png", 16, 1);
			UEngineSprite::CreateCutting("Player_Horse_Walk.png", 16, 1);
			UEngineSprite::CreateCutting("Player_Horse_Run.png", 16, 1);
			UEngineSprite::CreateCutting("Player_Horse_Rear.png", 16, 1);
			UEngineSprite::CreateCutting("Player_Horse_Eat.png", 16, 1);
			
			/* Images required to be cut */
		}
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
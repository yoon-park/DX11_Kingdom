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
			Dir.Move("Object");
			std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory();
			for (size_t i = 0; i < Directorys.size(); i++)
			{
				std::string Name = Directorys[i].GetFolderName();
				UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
			}
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
			UEngineSprite::CreateCutting("Merchant_Walk.png", 6, 1);
			UEngineSprite::CreateCutting("Vagrant_Idle.png", 6, 1);
			UEngineSprite::CreateCutting("Vagrant_Walk.png", 6, 1);
			UEngineSprite::CreateCutting("Vagrant_Run.png", 6, 1);
			UEngineSprite::CreateCutting("Vagrant_Die.png", 10, 1);
			UEngineSprite::CreateCutting("Villager_Idle.png", 6, 1);
			UEngineSprite::CreateCutting("Villager_Walk.png", 6, 1);
			UEngineSprite::CreateCutting("Villager_Run.png", 6, 1);
			UEngineSprite::CreateCutting("Villager_Bumped.png", 6, 1);
			UEngineSprite::CreateCutting("Villager_Getup.png", 6, 1);
			UEngineSprite::CreateCutting("Archer_Idle.png", 6, 1);
			UEngineSprite::CreateCutting("Archer_Walk.png", 6, 1);
			UEngineSprite::CreateCutting("Archer_Run.png", 6, 1);
			UEngineSprite::CreateCutting("Archer_Prep.png", 6, 1);
			UEngineSprite::CreateCutting("Archer_Shoot.png", 6, 1);
			UEngineSprite::CreateCutting("Builder_Idle.png", 8, 1);
			UEngineSprite::CreateCutting("Builder_Walk.png", 8, 1);
			UEngineSprite::CreateCutting("Builder_Run.png", 8, 1);
			UEngineSprite::CreateCutting("Builder_Work.png", 8, 1);
			
			/* Images required to be cut */
		}
	}

	/*
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
	*/

	GEngine->CreateLevel<ATitleGameMode>("TitleLevel");
	GEngine->CreateLevel<APlayGameMode>("PlayLevel");
	GEngine->ChangeLevel("PlayLevel");
}
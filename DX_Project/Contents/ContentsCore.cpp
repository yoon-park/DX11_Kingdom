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
			UEngineTexture::Load(File.GetFullPath());
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
	GEngine->ChangeLevel("TitleLevel");
}
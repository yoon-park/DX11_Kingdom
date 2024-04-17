#include "PreCompile.h"
#include "PlayGameMode.h"

#include "Player.h"
#include "Monster.h"
#include "PlayBack.h"
#include "PlayBackBack.h"

APlayGameMode::APlayGameMode()
{

}

APlayGameMode::~APlayGameMode()
{

}

void APlayGameMode::SetMainPlayer(std::shared_ptr<APlayer> _Player)
{
	MainPlayer = _Player;
}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	UContentsConstValue::MapTex = UEngineTexture::FindRes("Back.png");
	UContentsConstValue::MapTexScale = UContentsConstValue::MapTex->GetScale();

	{
		std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
		Camera->SetActorLocation(FVector(640.0f, -360.0f, -100.0f));
	}

	{
		std::shared_ptr<APlayer> Actor = GetWorld()->SpawnActor<APlayer>("Player", EObjectOrder::Player);
		Actor->SetActorLocation({ 640.0f, -400.0f, 100.0f });
		SetMainPlayer(Actor);
	}

	{
		std::shared_ptr<APlayBackBack> Hill = GetWorld()->SpawnActor<APlayBackBack>("Hill", EObjectOrder::Back);
		Hill->SetActorLocation({ 640.0f, -360.0f, 300.0f });
	}

	{
		std::shared_ptr<APlayBack> Rock = GetWorld()->SpawnActor<APlayBack>("Rock", EObjectOrder::Back);
		Rock->SetActorLocation({ 640.0f, -360.0f, 100.0f });
	}

	/*
	{
		std::shared_ptr<APlayBack> Back = GetWorld()->SpawnActor<APlayBack>("PlayBack");
		
		float TileSize = UContentsConstValue::TileSize;
		float4 TexScale = UContentsConstValue::MapTexScale;
		float4 ImageScale = { TexScale.X * TileSize, TexScale.Y * TileSize, 0.0f };

		Back->SetActorScale3D(ImageScale);
		Back->SetActorLocation({ ImageScale.hX(), -ImageScale.hY(), 500.0f });
	}
	*/
}


void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	{
		std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
		FVector PlayerLocation = MainPlayer->GetActorLocation();

		FVector NewLocation = Camera->GetActorLocation();
		NewLocation.X = PlayerLocation.X;
		NewLocation.Y = PlayerLocation.Y;

		Camera->SetActorLocation(NewLocation);
	}
}
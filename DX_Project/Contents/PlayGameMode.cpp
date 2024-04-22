#include "PreCompile.h"
#include "PlayGameMode.h"

#include "Sky.h"
#include "Back0.h"
#include "Back1.h"
#include "Back2.h"
#include "Back3.h"
#include "Back4.h"
#include "Ground.h"

#include "Player.h"
#include "Monster.h"

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

	//UContentsConstValue::MapTex = UEngineTexture::FindRes("Back.png");
	//UContentsConstValue::MapTexScale = UContentsConstValue::MapTex->GetScale();

	{
		std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
		Camera->SetActorLocation({ 0.0f, 60.0f, -100.0f });
	}
	{
		std::shared_ptr<APlayer> Player = GetWorld()->SpawnActor<APlayer>("Player", EObjectOrder::Player);
		Player->SetActorLocation({ 0.0f, 20.0f, 100.0f });
		SetMainPlayer(Player);
	}
	{
		std::shared_ptr<AGround> Ground = GetWorld()->SpawnActor<AGround>("Back0", EObjectOrder::Back);
		Ground->SetActorLocation({ 0.0f, 0.0f, 100.0f });
	}
	{
		std::shared_ptr<ABack0> Back0 = GetWorld()->SpawnActor<ABack0>("Back0", EObjectOrder::Back);
		Back0->SetActorLocation({ 0.0f, 30.0f, 100.0f });
	}
	{
		std::shared_ptr<ABack1> Back1 = GetWorld()->SpawnActor<ABack1>("Back1", EObjectOrder::Back);
		Back1->SetActorLocation({ 0.0f, 10.0f, 200.0f });
	}
	{
		std::shared_ptr<ABack2> Back2 = GetWorld()->SpawnActor<ABack2>("Back2", EObjectOrder::Back);
		Back2->SetActorLocation({ 0.0f, 160.0f, 500.0f });
	}
	{
		std::shared_ptr<ABack3> Back3 = GetWorld()->SpawnActor<ABack3>("Back3", EObjectOrder::Back);
		Back3->SetActorLocation({ 0.0f, 130.0f, 700.0f });
	}
	{
		std::shared_ptr<ABack3> Back4 = GetWorld()->SpawnActor<ABack3>("Back4", EObjectOrder::Back);
		Back4->SetActorLocation({ 0.0f, 150.0f, 900.0f });
	}
}


void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	{
		std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
		FVector PlayerLocation = MainPlayer->GetActorLocation();

		FVector NewLocation = Camera->GetActorLocation();
		NewLocation.X = PlayerLocation.X;
		//NewLocation.Y = PlayerLocation.Y;

		Camera->SetActorLocation(NewLocation);
	}
}
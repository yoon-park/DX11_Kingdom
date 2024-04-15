#include "PreCompile.h"
#include "PlayGameMode.h"

#include "Player.h"
#include "Monster.h"
#include "PlayBack.h"

APlayGameMode::APlayGameMode()
{

}

APlayGameMode::~APlayGameMode()
{

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
		Actor->SetActorLocation({ 640.0f, -360.0f, 200.0f });
	}

	{
		std::shared_ptr<AMonster> Actor = GetWorld()->SpawnActor<AMonster>("Monster", EObjectOrder::Monster);
		Actor->SetActorLocation({ 1040.0f, -360.0f, 200.0f });
	}

	{
		std::shared_ptr<APlayBack> Back = GetWorld()->SpawnActor<APlayBack>("PlayBack");
		
		float TileSize = UContentsConstValue::TileSize;
		float4 TexScale = UContentsConstValue::MapTexScale;
		float4 ImageScale = { TexScale.X * TileSize, TexScale.Y * TileSize, 0.0f };

		Back->SetActorScale3D(ImageScale);
		Back->SetActorLocation({ ImageScale.hX(), -ImageScale.hY(), 500.0f });
	}
}


void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
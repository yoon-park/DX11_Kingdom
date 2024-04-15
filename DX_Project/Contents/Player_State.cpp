#include "PreCompile.h"
#include "Player.h"

void APlayer::StateInit()
{
	State.CreateState("Die");
	State.CreateState("Idle");
	State.CreateState("Jump");
	State.CreateState("Run");

	State.SetStartFunction("Idle", [this]()
		{

		});

	State.SetUpdateFunction("Idle", std::bind(&APlayer::Idle, this, std::placeholders::_1));

	State.SetStartFunction("Run", std::bind(&APlayer::RunStart, this));
	State.SetUpdateFunction("Run", std::bind(&APlayer::Run, this, std::placeholders::_1));

	State.ChangeState("Idle");
}

void APlayer::Die(float _Update)
{

}

void APlayer::Idle(float _Update)
{
	if (IsPress('A') == true ||
		IsPress('D') == true || 
		IsPress('W') == true ||
		IsPress('S') == true)
	{
		State.ChangeState("Run");
		return;
	}
}

void APlayer::Jump(float _Update)
{

}

void APlayer::RunStart()
{

}

void APlayer::Run(float _DeltaTime)
{
	float Speed = 500.0f;

	if (IsPress('A') == true)
	{
		AddActorLocation(FVector::Left * _DeltaTime * Speed);
	}

	if (IsPress('D') == true)
	{
		AddActorLocation(FVector::Right * _DeltaTime * Speed);
	}

	if (IsPress('W') == true)
	{
		AddActorLocation(FVector::Up * _DeltaTime * Speed);
	}

	if (IsPress('S') == true)
	{
		AddActorLocation(FVector::Down * _DeltaTime * Speed);
	}

	if (IsPress(VK_NUMPAD1) == true)
	{
		AddActorRotation(float4{0.0f, 0.0f, 1.0f} * 360.0f * _DeltaTime);
	}

	if (IsPress(VK_NUMPAD2) == true)
	{
		AddActorRotation(float4{ 1.0f, 1.0f, 1.0f } * _DeltaTime);
	}

	if (IsPress(VK_NUMPAD4) == true)
	{
		Color.Y += _DeltaTime;
	}

	if (IsPress(VK_NUMPAD5) == true)
	{
		Color.Y -= _DeltaTime;
	}

	if (IsPress(VK_NUMPAD7) == true)
	{
		Color.Z += _DeltaTime;
	}

	if (IsPress(VK_NUMPAD8) == true)
	{
		Color.Z -= _DeltaTime;
	}

	std::shared_ptr<UEngineTexture> Tex = UContentsConstValue::MapTex;

#ifdef _DEBUG
	if (Tex == nullptr)
	{
		MsgBoxAssert("플레이어와 이미지 충돌체크 할 이미지가 존재하지 않습니다.");
	}
#endif

	float4 Pos = GetActorLocation();
	Pos /= UContentsConstValue::TileSize;
	Pos.Y = -Pos.Y;

	Color8Bit Color = Tex->GetColor(Pos, Color8Bit::Black);

	if (Color != Color8Bit::Black)
	{
		AddActorLocation(float4::Down * _DeltaTime * 100.0f);
	}
}
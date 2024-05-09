#include "PreCompile.h"
#include "Player.h"

#include "Coin.h"

void APlayer::StateInit()
{
	{
		State.CreateState("Idle");
		State.SetStartFunction("Idle", std::bind(&APlayer::IdleStart, this));
		State.SetUpdateFunction("Idle", std::bind(&APlayer::Idle, this, std::placeholders::_1));

		State.CreateState("Walk");
		State.SetStartFunction("Walk", std::bind(&APlayer::WalkStart, this));
		State.SetUpdateFunction("Walk", std::bind(&APlayer::Walk, this, std::placeholders::_1));

		State.CreateState("Run");
		State.SetStartFunction("Run", std::bind(&APlayer::RunStart, this));
		State.SetUpdateFunction("Run", std::bind(&APlayer::Run, this, std::placeholders::_1));

		State.CreateState("Rear");
		State.SetStartFunction("Rear", std::bind(&APlayer::RearStart, this));
		State.SetUpdateFunction("Rear", std::bind(&APlayer::Rear, this, std::placeholders::_1));

		State.CreateState("Eat");
		State.SetStartFunction("Eat", std::bind(&APlayer::EatStart, this));
		State.SetUpdateFunction("Eat", std::bind(&APlayer::Eat, this, std::placeholders::_1));

		State.CreateState("Pay");
		State.SetStartFunction("Pay", std::bind(&APlayer::PayStart, this));
		State.SetUpdateFunction("Pay", std::bind(&APlayer::Pay, this, std::placeholders::_1));
		State.SetEndFunction("Pay", std::bind(&APlayer::PayEnd, this));
	}
	{
		Speed = 0.0f;
		MoveVector = FVector::Zero;
		MoveAcc = 0.0f;
		JumpVector = FVector::Zero;
		GravityVector = FVector::Zero;
		GravityAcc = 0.0f;
		LastMoveVector = FVector::Zero;
	}

	State.ChangeState("Idle");
}

void APlayer::IdleStart()
{
	Renderer_Player->ChangeAnimation("Idle");
	Renderer_Horse->ChangeAnimation("Idle");

	SetMoveVector(FVector::Zero);
}

void APlayer::WalkStart()
{
	Renderer_Player->ChangeAnimation("Walk");
	Renderer_Horse->ChangeAnimation("Walk");

	Speed = 50.0f;
}

void APlayer::RunStart()
{
	Renderer_Player->ChangeAnimation("Run");
	Renderer_Horse->ChangeAnimation("Run");

	Speed = 150.0f;
}

void APlayer::RearStart()
{
	Renderer_Player->ChangeAnimation("Rear");
	Renderer_Horse->ChangeAnimation("Rear");

	SetMoveVector(FVector::Zero);
}

void APlayer::EatStart()
{
	Renderer_Player->ChangeAnimation("Eat");
	Renderer_Horse->ChangeAnimation("Eat");

	SetMoveVector(FVector::Zero);
}

void APlayer::PayStart()
{
	Renderer_Player->ChangeAnimation("Idle");
	Renderer_Horse->ChangeAnimation("Idle");

	SetMoveVector(FVector::Zero);

	IsPaying = true;
	CreateCoin();
}

void APlayer::Idle(float _DeltaTime)
{
	if (IsPress('A') == true || IsPress('D') == true)
	{
		if (IsPress(VK_SHIFT))
		{
			State.ChangeState("Run");
			return;
		}

		State.ChangeState("Walk");
		return;
	}

	if (IsDown(VK_DOWN) == true)
	{
		State.ChangeState("Pay");
		return;
	}
}

void APlayer::Walk(float _DeltaTime)
{
	if (IsPress(VK_SHIFT) == true)
	{
		State.ChangeState("Run");
		return;
	}

	if (IsFree('A') == true && IsFree('D') == true)
	{
		State.ChangeState("Idle");
		return;
	}

	if (IsPress('A') == true)
	{
		ChangeDir(EEngineDir::Left);
		SetMoveVector(FVector::Left * Speed);
	}

	if (IsPress('D') == true)
	{
		ChangeDir(EEngineDir::Right);
		SetMoveVector(FVector::Right * Speed);
	}
}

void APlayer::Run(float _DeltaTime)
{
	if (IsFree(VK_SHIFT) == true)
	{
		State.ChangeState("Walk");
		return;
	}

	if (IsFree('A') == true && IsFree('D') == true)
	{
		State.ChangeState("Idle");
		return;
	}

	if (IsPress('A') == true)
	{
		ChangeDir(EEngineDir::Left);
		SetMoveVector(FVector::Left * Speed);
	}

	if (IsPress('D') == true)
	{
		ChangeDir(EEngineDir::Right);
		SetMoveVector(FVector::Right * Speed);
	}
}

void APlayer::Rear(float _DeltaTime)
{

}

void APlayer::Eat(float _DeltaTime)
{

}

void APlayer::Pay(float _DeltaTime)
{
	if (IsFree(VK_DOWN) == true)
	{
		State.ChangeState("Idle");
		return;
	}

	if (IsPress(VK_DOWN) == true)
	{
		if (CurCoin->State.GetCurStateName() == "Wait")
		{
			if (CurCoinIndex + 1 == CurBuilding->GetRequiredCoin())
			{
				State.ChangeState("Idle");
				return;
			}
			else
			{
				CreateCoin();
				return;
			}
		}
	}
}

void APlayer::PayEnd()
{
	IsPaying = false;
	ResetCurCoin(); 
}
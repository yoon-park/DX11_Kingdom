#include "PreCompile.h"
#include "NPC.h"

void ANPC::StateInit()
{
	{
		State.CreateState("Vagrant_Idle");
		State.SetStartFunction("Vagrant_Idle", std::bind(&ANPC::Vagrant_IdleStart, this));
		State.SetUpdateFunction("Vagrant_Idle", std::bind(&ANPC::Vagrant_Idle, this, std::placeholders::_1));

		State.CreateState("Vagrant_Walk");
		State.SetStartFunction("Vagrant_Walk", std::bind(&ANPC::Vagrant_WalkStart, this));
		State.SetUpdateFunction("Vagrant_Walk", std::bind(&ANPC::Vagrant_Walk, this, std::placeholders::_1));

		State.CreateState("Vagrant_Run");
		State.SetStartFunction("Vagrant_Run", std::bind(&ANPC::Vagrant_RunStart, this));
		State.SetUpdateFunction("Vagrant_Run", std::bind(&ANPC::Vagrant_Run, this, std::placeholders::_1));

		State.CreateState("Villager_Idle");
		State.SetStartFunction("Villager_Idle", std::bind(&ANPC::Villager_IdleStart, this));
		State.SetUpdateFunction("Villager_Idle", std::bind(&ANPC::Villager_Idle, this, std::placeholders::_1));

		State.CreateState("Villager_Walk");
		State.SetStartFunction("Villager_Walk", std::bind(&ANPC::Villager_WalkStart, this));
		State.SetUpdateFunction("Villager_Walk", std::bind(&ANPC::Villager_Walk, this, std::placeholders::_1));

		State.CreateState("Villager_Run");
		State.SetStartFunction("Villager_Run", std::bind(&ANPC::Villager_RunStart, this));
		State.SetUpdateFunction("Villager_Run", std::bind(&ANPC::Villager_Run, this, std::placeholders::_1));

		State.CreateState("Villager_Bumped");
		State.SetStartFunction("Villager_Bumped", std::bind(&ANPC::Villager_BumpedStart, this));
		State.SetUpdateFunction("Villager_Bumped", std::bind(&ANPC::Villager_Bumped, this, std::placeholders::_1));

		State.CreateState("Villager_Getup");
		State.SetStartFunction("Villager_Getup", std::bind(&ANPC::Villager_GetupStart, this));
		State.SetUpdateFunction("Villager_Getup", std::bind(&ANPC::Villager_Getup, this, std::placeholders::_1));

		State.CreateState("Archer_Idle");
		State.SetStartFunction("Archer_Idle", std::bind(&ANPC::Archer_IdleStart, this));
		State.SetUpdateFunction("Archer_Idle", std::bind(&ANPC::Archer_Idle, this, std::placeholders::_1));

		State.CreateState("Archer_Walk");
		State.SetStartFunction("Archer_Walk", std::bind(&ANPC::Archer_WalkStart, this));
		State.SetUpdateFunction("Archer_Walk", std::bind(&ANPC::Archer_Walk, this, std::placeholders::_1));

		State.CreateState("Archer_Run");
		State.SetStartFunction("Archer_Run", std::bind(&ANPC::Archer_RunStart, this));
		State.SetUpdateFunction("Archer_Run", std::bind(&ANPC::Archer_Run, this, std::placeholders::_1));

		State.CreateState("Archer_Prep");
		State.SetStartFunction("Archer_Prep", std::bind(&ANPC::Archer_PrepStart, this));
		State.SetUpdateFunction("Archer_Prep", std::bind(&ANPC::Archer_Prep, this, std::placeholders::_1));

		State.CreateState("Archer_Shoot");
		State.SetStartFunction("Archer_Shoot", std::bind(&ANPC::Archer_ShootStart, this));
		State.SetUpdateFunction("Archer_Shoot", std::bind(&ANPC::Archer_Shoot, this, std::placeholders::_1));

		State.CreateState("Builder_Idle");
		State.SetStartFunction("Builder_Idle", std::bind(&ANPC::Builder_IdleStart, this));
		State.SetUpdateFunction("Builder_Idle", std::bind(&ANPC::Builder_Idle, this, std::placeholders::_1));

		State.CreateState("Builder_Walk");
		State.SetStartFunction("Builder_Walk", std::bind(&ANPC::Builder_WalkStart, this));
		State.SetUpdateFunction("Builder_Walk", std::bind(&ANPC::Builder_Walk, this, std::placeholders::_1));

		State.CreateState("Builder_Run");
		State.SetStartFunction("Builder_Run", std::bind(&ANPC::Builder_RunStart, this));
		State.SetUpdateFunction("Builder_Run", std::bind(&ANPC::Builder_Run, this, std::placeholders::_1));

		State.CreateState("Builder_Work");
		State.SetStartFunction("Builder_Work", std::bind(&ANPC::Builder_WorkStart, this));
		State.SetUpdateFunction("Builder_Work", std::bind(&ANPC::Builder_Work, this, std::placeholders::_1));
	}
	{
		// init
	}

	State.ChangeState("Vagrant_Idle");
}

void ANPC::Vagrant_IdleStart()
{
	Renderer->ChangeAnimation("Vagrant_Idle");
}

void ANPC::Vagrant_Idle(float _DeltaTime)
{

}

void ANPC::Vagrant_WalkStart()
{
	Renderer->ChangeAnimation("Vagrant_Walk");
}

void ANPC::Vagrant_Walk(float _DeltaTime)
{

}

void ANPC::Vagrant_RunStart()
{
	Renderer->ChangeAnimation("Vagrant_Run");
}

void ANPC::Vagrant_Run(float _DeltaTime)
{

}

void ANPC::Villager_IdleStart()
{
	Renderer->ChangeAnimation("Villager_Idle");
}

void ANPC::Villager_Idle(float _DeltaTime)
{

}

void ANPC::Villager_WalkStart()
{
	Renderer->ChangeAnimation("Villager_Walk");
}

void ANPC::Villager_Walk(float _DeltaTime)
{

}

void ANPC::Villager_RunStart()
{
	Renderer->ChangeAnimation("Villager_Run");
}

void ANPC::Villager_Run(float _DeltaTime)
{

}

void ANPC::Villager_BumpedStart()
{
	Renderer->ChangeAnimation("Villager_Bumped");
}

void ANPC::Villager_Bumped(float _DeltaTime)
{

}

void ANPC::Villager_GetupStart()
{
	Renderer->ChangeAnimation("Villager_Getup");
}

void ANPC::Villager_Getup(float _DeltaTime)
{

}

void ANPC::Archer_IdleStart()
{
	Renderer->ChangeAnimation("Archer_Idle");
}

void ANPC::Archer_Idle(float _DeltaTime)
{

}

void ANPC::Archer_WalkStart()
{
	Renderer->ChangeAnimation("Archer_Walk");
}

void ANPC::Archer_Walk(float _DeltaTime)
{

}

void ANPC::Archer_RunStart()
{
	Renderer->ChangeAnimation("Archer_Run");
}

void ANPC::Archer_Run(float _DeltaTime)
{

}

void ANPC::Archer_PrepStart()
{
	Renderer->ChangeAnimation("Archer_Prep");
}

void ANPC::Archer_Prep(float _DeltaTime)
{

}

void ANPC::Archer_ShootStart()
{
	Renderer->ChangeAnimation("Archer_Shoot");
}

void ANPC::Archer_Shoot(float _DeltaTime)
{

}

void ANPC::Builder_IdleStart()
{
	Renderer->ChangeAnimation("Builder_Idle");
}

void ANPC::Builder_Idle(float _DeltaTime)
{

}

void ANPC::Builder_WalkStart()
{
	Renderer->ChangeAnimation("Builder_Walk");
}

void ANPC::Builder_Walk(float _DeltaTime)
{

}

void ANPC::Builder_RunStart()
{
	Renderer->ChangeAnimation("Builder_Run");
}

void ANPC::Builder_Run(float _DeltaTime)
{

}

void ANPC::Builder_WorkStart()
{
	Renderer->ChangeAnimation("Builder_Work");
}

void ANPC::Builder_Work(float _DeltaTime)
{

}
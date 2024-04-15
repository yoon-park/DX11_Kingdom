#include "PreCompile.h"
#include "StateManager.h"

UStateManager::UStateManager()
{

}

UStateManager::~UStateManager()
{

}

void UStateManager::SetFunction(
	std::string_view _Name,
	std::function<void()> _Start /*= nullptr*/,
	std::function<void(float)> _Update /*= nullptr*/,
	std::function<void()> _End /*= nullptr*/
)
{
	std::shared_ptr<UState> State = FindState(_Name);

	if (State == nullptr)
	{
		MsgBoxAssert("존재하지 않는 스테이트입니다.");
	}

	State->Start = _Start;
	State->Update = _Update;
	State->End = _End;
}

void UStateManager::SetStartFunction(std::string_view _Name, std::function<void()> _Function /*= nullptr*/)
{
	std::shared_ptr<UState> State = FindState(_Name);

	if (State == nullptr)
	{
		MsgBoxAssert("존재하지 않는 스테이트입니다.");
	}

	State->Start = _Function;
}

void UStateManager::SetUpdateFunction(std::string_view _Name, std::function<void(float)> _Function /*= nullptr*/)
{
	std::shared_ptr<UState> State = FindState(_Name);

	if (State == nullptr)
	{
		MsgBoxAssert("존재하지 않는 스테이트입니다.");
	}

	State->Update = _Function;
}

void UStateManager::SetEndFunction(std::string_view _Name, std::function<void()> _Function /*= nullptr*/)
{
	std::shared_ptr<UState> State = FindState(_Name);

	if (State == nullptr)
	{
		MsgBoxAssert("존재하지 않는 스테이트입니다.");
	}

	State->End = _Function;
}

void UStateManager::CreateState(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);
	States[UpperName] = std::make_shared<UState>();
	States[UpperName]->SetName(_Name);
}

void UStateManager::ChangeState(std::string_view _Name)
{
	if (CurState != nullptr && CurState->End != nullptr)
	{
		CurState->End();
	}

	CurState = FindState(_Name);

	if (CurState != nullptr && CurState->Start != nullptr)
	{
		CurState->Start();
	}

	if (CurState == nullptr)
	{
		MsgBoxAssert("존재하지 않는 스테이트로 변경하려 했습니다. : " + std::string(_Name));
	}
}

std::shared_ptr<UState> UStateManager::FindState(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (States.contains(UpperName) == false)
	{
		return nullptr;
	}

	return States[UpperName];
}

void UStateManager::Update(float _Time)
{
	if (CurState == nullptr)
	{
		MsgBoxAssert("스테이트를 설정하지 않고 스테이트매니저를 사용하려 했습니다.");
	}

	CurState->Update(_Time);
}
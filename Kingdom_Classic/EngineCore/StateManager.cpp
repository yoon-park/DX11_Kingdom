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
		MsgBoxAssert("�������� �ʴ� ������Ʈ�Դϴ�.");
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
		MsgBoxAssert("�������� �ʴ� ������Ʈ�Դϴ�.");
	}

	State->Start = _Function;
}

void UStateManager::SetUpdateFunction(std::string_view _Name, std::function<void(float)> _Function /*= nullptr*/)
{
	std::shared_ptr<UState> State = FindState(_Name);

	if (State == nullptr)
	{
		MsgBoxAssert("�������� �ʴ� ������Ʈ�Դϴ�.");
	}

	State->Update = _Function;
}

void UStateManager::SetEndFunction(std::string_view _Name, std::function<void()> _Function /*= nullptr*/)
{
	std::shared_ptr<UState> State = FindState(_Name);

	if (State == nullptr)
	{
		MsgBoxAssert("�������� �ʴ� ������Ʈ�Դϴ�.");
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
		MsgBoxAssert("�������� �ʴ� ������Ʈ�� �����Ϸ� �߽��ϴ�. : " + std::string(_Name));
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
		MsgBoxAssert("������Ʈ�� �������� �ʰ� ������Ʈ�Ŵ����� ����Ϸ� �߽��ϴ�.");
	}

	CurState->Update(_Time);
}
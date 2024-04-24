#pragma once

class UState : public UNameObject
{
public:
	std::function<void()> Start;
	std::function<void(float)> Update;
	std::function<void()> End;
};

class UStateManager
{
public:
	UStateManager();
	~UStateManager();

	UStateManager(const UStateManager& _Other) = delete;
	UStateManager(UStateManager&& _Other) noexcept = delete;
	UStateManager& operator=(const UStateManager& _Other) = delete;
	UStateManager& operator=(UStateManager&& _Other) noexcept = delete;

	inline std::string GetCurStateName() const
	{
		return CurState->GetName();
	}

	void SetFunction(
		std::string_view _Name,
		std::function<void()> _Start = nullptr,
		std::function<void(float)> _Update = nullptr,
		std::function<void()> _End = nullptr
	);
	void SetStartFunction(std::string_view _Name, std::function<void()> _Function = nullptr);
	void SetUpdateFunction(std::string_view _Name, std::function<void(float)> _Function = nullptr);
	void SetEndFunction(std::string_view _Name, std::function<void()> _Function = nullptr);

	void CreateState(std::string_view _Name);
	void ChangeState(std::string_view _Name);
	std::shared_ptr<UState> FindState(std::string_view _Name);
	void Update(float _Time);

protected:

private:
	std::shared_ptr<UState> CurState = nullptr;

	std::map<std::string, std::shared_ptr<UState>> States;
};
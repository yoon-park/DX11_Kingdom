#pragma once

#define GENERATED_BODY(Parent) \
	typedef Parent Super;

class UEngineTickCallback
{
public:
	float Time;
	std::function<void()> Callback;
};

class ULevel;

class UTickObject
{
public:
	UTickObject();
	~UTickObject();

	UTickObject(const UTickObject& _Other) = delete;
	UTickObject(UTickObject&& _Other) noexcept = delete;
	UTickObject& operator=(const UTickObject& _Other) = delete;
	UTickObject& operator=(UTickObject&& _Other) noexcept = delete;

	int GetOrder()
	{
		return Order;
	}

	void SetOrder(int _Order)
	{
		Order = _Order;
	}

	void DelayCallback(float _Time, std::function<void()> _Callback)
	{
		if (_Callback == nullptr)
		{
			MsgBoxAssert("콜백 기능이 nullptr 입니다.");
		}

		for (size_t i = 0; i < Callbacks.size(); i++)
		{
			if (Callbacks[i] == nullptr)
			{
				Callbacks[i] = std::make_shared<UEngineTickCallback>(_Time, _Callback);
				return;
			}
		}

		Callbacks.push_back(std::make_shared<UEngineTickCallback>(_Time, _Callback));
	}

protected:
	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);

	virtual void LevelStart(ULevel* _PrevLevel);
	virtual void LevelEnd(ULevel* _NextLevel);

private:
	int Order = 0;

	std::vector<std::shared_ptr<UEngineTickCallback>> Callbacks;
};
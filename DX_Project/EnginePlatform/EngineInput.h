#pragma once

class UEngineInput
{
	friend class UInputInitCreator;

private:
	class EngineKey
	{
		friend UEngineInput;

	public:
		bool Down = false; 
		bool Press = false;
		bool Up = false;
		bool Free = true;

		float PressTime = 0.0f;
		float UpTime = 0.0f;

		int Key = -1;

		void KeyCheck(float _DeltaTime);

		EngineKey()
		{

		}

		EngineKey(int _Key)
			: Key(_Key)
		{

		}
	};

public:
	UEngineInput();
	~UEngineInput();

	UEngineInput(const UEngineInput& _Other) = delete;
	UEngineInput(UEngineInput&& _Other) noexcept = delete;
	UEngineInput& operator=(const UEngineInput& _Other) = delete;
	UEngineInput& operator=(UEngineInput&& _Other) noexcept = delete;

	static float GetPressTime(int _Key)
	{
		if (AllKeys.contains(_Key) == false)
		{
			MsgBoxAssert("�Է¼����� �������� �ʴ� Ű �Դϴ�.");
		}

		return AllKeys[_Key].PressTime;
	}

	static bool IsDown(int _Key)
	{
		if (AllKeys.contains(_Key) == false)
		{
			MsgBoxAssert("�Է¼����� �������� �ʴ� Ű �Դϴ�.");
		}

		return AllKeys[_Key].Down;
	}

	static bool IsPress(int _Key)
	{
		if (AllKeys.contains(_Key) == false)
		{
			MsgBoxAssert("�Է¼����� �������� �ʴ� Ű �Դϴ�.");
		}

		return AllKeys[_Key].Press;
	}

	static bool IsUp(int _Key)
	{
		if (AllKeys.contains(_Key) == false)
		{
			MsgBoxAssert("�Է¼����� �������� �ʴ� Ű �Դϴ�.");
		}

		return AllKeys[_Key].Up;
	}

	static bool IsFree(int _Key)
	{
		if (AllKeys.contains(_Key) == false)
		{
			MsgBoxAssert("�Է¼����� �������� �ʴ� Ű �Դϴ�.");
		}

		return AllKeys[_Key].Free;
	}

	static bool IsDoubleClick(int _Key, float _ClickTime)
	{
		if (AllKeys.contains(_Key) == false)
		{
			MsgBoxAssert("�Է¼����� �������� �ʴ� Ű �Դϴ�.");
		}

		bool Value = AllKeys[_Key].Down;
		float Time = AllKeys[_Key].UpTime;

		if (AllKeys[_Key].Down && (AllKeys[_Key].UpTime < _ClickTime) == true)
		{
			return true;
		}

		return false;
	}

	static bool IsAnykeyDown()
	{
		return AnykeyDown;
	}

	static bool IsAnykeyPress()
	{
		return AnykeyPress;
	}

	static bool IsAnykeyUp()
	{
		return AnykeyUp;
	}

	static bool IsAnykeyFree()
	{
		return AnykeyFree;
	}

	static void KeyCheckTick(float _DeltaTime);

protected:
	static std::map<int, EngineKey> AllKeys;

	static bool AnykeyDown;
	static bool AnykeyPress;
	static bool AnykeyUp;
	static bool AnykeyFree;

	int Value;

private:
	static void InputInit();
};

